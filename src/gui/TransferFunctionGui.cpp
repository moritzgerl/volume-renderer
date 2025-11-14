#include <gui/TransferFunctionGui.h>
#include <gui/GuiUpdateFlags.h>

#include <transferfunction/InterpolateTransferFunction.h>
#include <transferfunction/TransferFunction.h>

#include <imgui.h>
#include <algorithm>
#include <cmath>
#include <span>
#include <string>

namespace
{
    const ImGuiColorEditFlags colorPickerFlags = ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_Float;
} // anonymous namespace

TransferFunctionGui::TransferFunctionGui(TransferFunction& transferFunction, GuiUpdateFlags& guiUpdateFlags)
    : m_isActive{ false }
    , m_isHovered{ false }
    , m_isShiftPressed{ false }
    , m_wasClicked{ false }
    , m_numActivePoints{ 0 }
    , m_draggedPointIndex{ std::nullopt }
    , m_colorPickerPointIndex{ std::nullopt }
    , m_hoveredPointIndex{ std::nullopt }
    , m_interactiveAreaHeight{ 0.0f }
    , m_gradientHeight{ 15.0f }
    , m_plotSize{}
    , m_plotPos{}
    , m_mousePos{}
    , m_transferFunction{transferFunction}
    , m_guiUpdateFlags{guiUpdateFlags}
{
}

void TransferFunctionGui::Update()
{
    UpdateState();
    HandleInteraction();
    Draw();
}

void TransferFunctionGui::UpdateState()
{
    m_plotSize = ImGui::GetContentRegionAvail();
    m_plotPos = ImGui::GetCursorScreenPos();

    ImGui::InvisibleButton("TransferFunctionPlot", m_plotSize);
    
    m_isActive = ImGui::IsItemActive();
    m_isHovered = ImGui::IsItemHovered();
    m_isShiftPressed = ImGui::GetIO().KeyShift;
    m_mousePos = ImGui::GetMousePos();
    m_numActivePoints = m_transferFunction.GetNumActivePoints();
    m_interactiveAreaHeight = m_plotSize.y - m_gradientHeight;
}

void TransferFunctionGui::HandleInteraction()
{
    // Check if hovering over a control point
    m_hoveredPointIndex = std::nullopt;
    if (m_isHovered)
    {
        float minDist = 15.0f; // Hover radius
        for (size_t i = 0; i < m_numActivePoints; ++i)
        {
            auto& point = m_transferFunction[i];
            float x = m_plotPos.x + point.value * m_plotSize.x;
            float y = m_plotPos.y + m_plotSize.y - m_gradientHeight - (point.opacity * m_interactiveAreaHeight);

            float dist = std::sqrt((m_mousePos.x - x) * (m_mousePos.x - x) + (m_mousePos.y - y) * (m_mousePos.y - y));
            if (dist < minDist)
            {
                minDist = dist;
                m_hoveredPointIndex = i;
            }
        }
    }

    // Handle double-click to open color picker
    if (m_isActive && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
    {
        float minDist = 15.0f;
        for (size_t i = 0; i < m_numActivePoints; ++i)
        {
            auto& point = m_transferFunction[i];
            float x = m_plotPos.x + point.value * m_plotSize.x;
            float y = m_plotPos.y + m_plotSize.y - m_gradientHeight - (point.opacity * m_interactiveAreaHeight);

            float dist = std::sqrt((m_mousePos.x - x) * (m_mousePos.x - x) + (m_mousePos.y - y) * (m_mousePos.y - y));
            if (dist < minDist)
            {
                minDist = dist;
                m_colorPickerPointIndex = i;
                break;
            }
        }
    }

    // Handle single click to add new control point or Shift+Click to delete
    if (m_isActive && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
    {
        // Check if we clicked near an existing point
        float minDist = 15.0f; // Click radius
        std::optional<size_t> clickedPointIndex = std::nullopt;
        for (size_t i = 0; i < m_numActivePoints; ++i)
        {
            auto& point = m_transferFunction[i];
            float x = m_plotPos.x + point.value * m_plotSize.x;
            float y = m_plotPos.y + m_plotSize.y - m_gradientHeight - (point.opacity * m_interactiveAreaHeight);

            float dist = std::sqrt((m_mousePos.x - x) * (m_mousePos.x - x) + (m_mousePos.y - y) * (m_mousePos.y - y));
            if (dist < minDist)
            {
                minDist = dist;
                clickedPointIndex = i;
            }
        }

        // If Shift is held and we clicked on a point, delete it
        if (ImGui::GetIO().KeyShift && clickedPointIndex)
        {
            // Shift remaining points down
            for (size_t j = clickedPointIndex.value(); j < m_numActivePoints - 1; ++j)
            {
                m_transferFunction[j] = m_transferFunction[j + 1];
            }
            m_transferFunction.SetNumActivePoints(m_numActivePoints - 1);
            m_guiUpdateFlags.transferFunctionChanged = true;
            m_wasClicked = true;
        }
        // If we didn't click near an existing point, add a new one
        else if (!clickedPointIndex && m_numActivePoints < TransferFunctionConstants::maxNumControlPoints)
        {
            // Calculate new point position
            float newValue = std::clamp((m_mousePos.x - m_plotPos.x) / m_plotSize.x, 0.0f, 1.0f);
            float newOpacity = std::clamp(1.0f - ((m_mousePos.y - m_plotPos.y) / m_interactiveAreaHeight), 0.0f, 1.0f);

            // Find the insertion position to keep points sorted by value
            size_t insertIndex = m_numActivePoints;
            for (size_t j = 0; j < m_numActivePoints; ++j)
            {
                if (m_transferFunction[j].value > newValue)
                {
                    insertIndex = j;
                    break;
                }
            }

            // Shift existing points to make room for the new point
            for (size_t j = m_numActivePoints; j > insertIndex; --j)
            {
                m_transferFunction[j] = m_transferFunction[j - 1];
            }

            // Interpolate color from surrounding points
            glm::vec3 newColor = glm::vec3(0.5f);
            if (insertIndex > 0 && insertIndex < m_numActivePoints)
            {
                // Between two points
                auto& p0 = m_transferFunction[insertIndex - 1];
                auto& p1 = m_transferFunction[insertIndex + 1];
                float t = (newValue - p0.value) / (p1.value - p0.value);
                newColor = glm::mix(p0.color, p1.color, t);
            }
            else if (insertIndex == 0 && m_numActivePoints > 0)
            {
                // Before the first point
                newColor = m_transferFunction[1].color;
            }
            else if (insertIndex == m_numActivePoints && m_numActivePoints > 0)
            {
                // After the last point
                newColor = m_transferFunction[insertIndex - 1].color;
            }

            // Insert the new point at the correct position
            m_transferFunction[insertIndex].value = newValue;
            m_transferFunction[insertIndex].color = newColor;
            m_transferFunction[insertIndex].opacity = newOpacity;

            m_transferFunction.IncrementNumActivePoints();

            m_guiUpdateFlags.transferFunctionChanged = true;
            m_wasClicked = true;
        }
    }

    if (m_isActive && ImGui::IsMouseDragging(ImGuiMouseButton_Left, 0.0f) && !m_wasClicked)
    {
        // If we're dragging, find the closest point on first click or continue dragging
        if (!m_draggedPointIndex)
        {
            float minDist = 15.0f; // Click radius
            for (size_t i = 0; i < m_numActivePoints; ++i)
            {
                auto& point = m_transferFunction[i];
                float x = m_plotPos.x + point.value * m_plotSize.x;
                float y = m_plotPos.y + m_plotSize.y - m_gradientHeight - (point.opacity * m_interactiveAreaHeight);

                float dist = std::sqrt((m_mousePos.x - x) * (m_mousePos.x - x) + (m_mousePos.y - y) * (m_mousePos.y - y));
                if (dist < minDist)
                {
                    minDist = dist;
                    m_draggedPointIndex = i;
                }
            }
        }

        // Update the dragged point
        if (m_draggedPointIndex)
        {
            size_t draggedIndex = m_draggedPointIndex.value();
            auto& point = m_transferFunction[draggedIndex];

            // Update value (x-axis) - clamp to prevent crossing adjacent points
            float newValue = (m_mousePos.x - m_plotPos.x) / m_plotSize.x;

            // Get boundaries from adjacent control points
            float minValue = 0.0f;
            float maxValue = 1.0f;

            if (draggedIndex > 0)
            {
                minValue = m_transferFunction[draggedIndex - 1].value + 0.001f;
            }

            if (draggedIndex < m_numActivePoints - 1)
            {
                maxValue = m_transferFunction[draggedIndex + 1].value - 0.001f;
            }

            point.value = std::clamp(newValue, minValue, maxValue);

            // Update opacity (y-axis) - clamp to [0, 1]
            float newOpacity = 1.0f - ((m_mousePos.y - m_plotPos.y) / m_interactiveAreaHeight);
            point.opacity = std::clamp(newOpacity, 0.0f, 1.0f);

            m_guiUpdateFlags.transferFunctionChanged = true;
        }
    }
    else
    {
        // Reset dragged point when mouse is released
        m_draggedPointIndex = std::nullopt;
        m_wasClicked = false;
    }
}

void TransferFunctionGui::Draw()
{
    // Set cursor when hovering over a control point
    if (m_hoveredPointIndex && !m_isShiftPressed)
    {
        ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
    }

    ImDrawList* drawList = ImGui::GetWindowDrawList();

    // Draw background (transparent)
    drawList->AddRectFilled(m_plotPos, ImVec2(m_plotPos.x + m_plotSize.x, m_plotPos.y + m_plotSize.y), IM_COL32(0, 0, 0, 255));

    // Draw grid lines
    for (int i = 0; i <= 10; ++i)
    {
        float y = m_plotPos.y + (m_plotSize.y / 10.0f) * i;
        drawList->AddLine(ImVec2(m_plotPos.x, y), ImVec2(m_plotPos.x + m_plotSize.x, y), IM_COL32(80, 80, 80, 100));

        float x = m_plotPos.x + (m_plotSize.x / 10.0f) * i;
        drawList->AddLine(ImVec2(x, m_plotPos.y), ImVec2(x, m_plotPos.y + m_plotSize.y), IM_COL32(80, 80, 80, 100));
    }

    // Draw color gradient at the bottom
    const int gradientSteps = 256;
    for (int i = 0; i < gradientSteps - 1; ++i)
    {
        float t = static_cast<float>(i) / (gradientSteps - 1);
        float nextT = static_cast<float>(i + 1) / (gradientSteps - 1);

        // Find surrounding control points and interpolate color
        glm::vec3 color = glm::vec3(0.5f);
        for (size_t j = 0; j < m_numActivePoints; ++j)
        {
            if (m_transferFunction[j].value >= t)
            {
                if (j == 0)
                {
                    color = m_transferFunction[j].color;
                }
                else
                {
                    auto& p0 = m_transferFunction[j - 1];
                    auto& p1 = m_transferFunction[j];
                    float localT = (t - p0.value) / (p1.value - p0.value);
                    color = glm::mix(p0.color, p1.color, localT);
                }
                break;
            }
            else if (j == m_numActivePoints - 1)
            {
                color = m_transferFunction[j].color;
            }
        }

        float x1 = m_plotPos.x + t * m_plotSize.x;
        float x2 = m_plotPos.x + nextT * m_plotSize.x;
        float y1 = m_plotPos.y + m_plotSize.y - m_gradientHeight;
        float y2 = m_plotPos.y + m_plotSize.y;

        ImU32 col = IM_COL32(static_cast<int>(color.r * 255), static_cast<int>(color.g * 255), static_cast<int>(color.b * 255), 255);
        drawList->AddRectFilled(ImVec2(x1, y1), ImVec2(x2, y2), col);
    }

    // Draw opacity curve using shared interpolation
    if (m_numActivePoints >= 2)
    {
        const int totalSegments = 100;  // Total segments across entire curve for smooth rendering
        const auto activePoints = std::span{m_transferFunction.GetControlPoints().data(), m_numActivePoints};

        for (int seg = 0; seg < totalSegments; ++seg)
        {
            float value0 = static_cast<float>(seg) / totalSegments;
            float value1 = static_cast<float>(seg + 1) / totalSegments;

            // Evaluate transfer function at segment endpoints using shared interpolation
            glm::vec4 rgba0 = InterpolateTransferFunction(value0, activePoints);
            glm::vec4 rgba1 = InterpolateTransferFunction(value1, activePoints);

            float x0 = m_plotPos.x + value0 * m_plotSize.x;
            float y0 = m_plotPos.y + m_plotSize.y - m_gradientHeight - (rgba0.a * (m_plotSize.y - m_gradientHeight));
            float x1 = m_plotPos.x + value1 * m_plotSize.x;
            float y1 = m_plotPos.y + m_plotSize.y - m_gradientHeight - (rgba1.a * (m_plotSize.y - m_gradientHeight));

            drawList->AddLine(ImVec2(x0, y0), ImVec2(x1, y1), IM_COL32(255, 255, 255, 200), 1.8f);
        }
    }

    // Draw control points
    for (size_t i = 0; i < m_numActivePoints; ++i)
    {
        auto& point = m_transferFunction[i];
        float x = m_plotPos.x + point.value * m_plotSize.x;
        float y = m_plotPos.y + m_plotSize.y - m_gradientHeight - (point.opacity * m_interactiveAreaHeight);

        // Determine color and size based on state
        bool isDragged = (m_draggedPointIndex == i);
        bool isHoveredForDelete = (m_hoveredPointIndex == i && ImGui::GetIO().KeyShift);

        float radius = isDragged ? 9.0f : 8.0f;
        ImU32 fillColor;

        if (isHoveredForDelete)
        {
            fillColor = IM_COL32(255, 50, 50, 220);  // Red for delete
        }
        else if (isDragged)
        {
            fillColor = IM_COL32(0, 253, 0, 200);    // Green for dragging
        }
        else
        {
            // Use the control point's actual color
            fillColor = IM_COL32(
                static_cast<int>(point.color.r * 255),
                static_cast<int>(point.color.g * 255),
                static_cast<int>(point.color.b * 255),
                255
            );
        }

        drawList->AddCircleFilled(ImVec2(x, y), radius, fillColor);
        drawList->AddCircle(ImVec2(x, y), radius, IM_COL32(0, 0, 0, 200), 12, 1.0f);
    }

    // Color picker popup
    if (m_colorPickerPointIndex && m_colorPickerPointIndex.value() < m_numActivePoints)
    {
        ImGui::OpenPopup("ColorPickerPopup");
    }

    if (ImGui::BeginPopup("ColorPickerPopup"))
    {
        if (m_colorPickerPointIndex && m_colorPickerPointIndex.value() < m_numActivePoints)
        {
            size_t index = m_colorPickerPointIndex.value();
            auto& point = m_transferFunction[index];
            ImGui::Text("Control Point %zu Color", index);
            if (ImGui::ColorPicker3("##picker", (float*)&point.color, colorPickerFlags))
            {
                m_guiUpdateFlags.transferFunctionChanged = true;
            }
            if (ImGui::Button("Close") || ImGui::IsKeyPressed(ImGuiKey_Escape))
            {
                m_colorPickerPointIndex = std::nullopt;
                ImGui::CloseCurrentPopup();
            }
        }
        ImGui::EndPopup();
    }
    else
    {
        // Reset if popup was closed by clicking outside
        if (m_colorPickerPointIndex && !ImGui::IsPopupOpen("ColorPickerPopup"))
        {
            m_colorPickerPointIndex = std::nullopt;
        }
    }
}
