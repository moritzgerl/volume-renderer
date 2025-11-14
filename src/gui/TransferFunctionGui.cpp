#include <gui/TransferFunctionGui.h>
#include <gui/GuiUpdateFlags.h>

#include <transferfunction/InterpolateTransferFunction.h>
#include <transferfunction/TransferFunction.h>

#include <imgui.h>
#include <algorithm>
#include <cmath>
#include <ranges>
#include <span>
#include <string>

namespace
{
    const ImGuiColorEditFlags colorPickerFlags = ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_Float;
}

namespace Constants
{
    constexpr float interactionRadius = 15.0f;
}

TransferFunctionGui::TransferFunctionGui(TransferFunction& transferFunction, GuiUpdateFlags& guiUpdateFlags)
    : m_wasClicked{ false }
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
    PrepareInteraction();
    HandleInteraction();
    Draw();
}

void TransferFunctionGui::PrepareInteraction()
{
    m_plotSize = ImGui::GetContentRegionAvail();
    m_plotPos = ImGui::GetCursorScreenPos();
    ImGui::InvisibleButton("TransferFunctionPlot", m_plotSize);
    m_mousePos = ImGui::GetMousePos();
    m_numActivePoints = m_transferFunction.GetNumActivePoints();
    m_interactiveAreaHeight = m_plotSize.y - m_gradientHeight;
}

void TransferFunctionGui::HandleInteraction()
{
    HandleHover();
    HandleDoubleClick();
    HandleClick();
    HandleDrag();
}

// For interacting with control points
void TransferFunctionGui::HandleHover()
{
    m_hoveredPointIndex = std::nullopt;

    if (ImGui::IsItemHovered())
    {
        m_hoveredPointIndex = GetNearestPointIndex();
    }
}

// For opening color picker
void TransferFunctionGui::HandleDoubleClick()
{
    if (ImGui::IsItemActive() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
    {
        m_colorPickerPointIndex = GetNearestPointIndex();
    }
}

// For adding / removing control points
void TransferFunctionGui::HandleClick()
{
    if (ImGui::IsItemActive() && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
    {
        std::optional<size_t> clickedPointIndex = GetNearestPointIndex();

        if (ImGui::GetIO().KeyShift && clickedPointIndex)
        {
            m_transferFunction.RemovePoint(clickedPointIndex.value());
            m_guiUpdateFlags.transferFunctionChanged = true;
            m_wasClicked = true;
        }

        else if (!clickedPointIndex && m_numActivePoints < TransferFunctionConstants::maxNumControlPoints)
        {
            const float newValue = std::clamp((m_mousePos.x - m_plotPos.x) / m_plotSize.x, 0.0f, 1.0f);
            const float newOpacity = std::clamp(1.0f - ((m_mousePos.y - m_plotPos.y) / m_interactiveAreaHeight), 0.0f, 1.0f);

            m_transferFunction.AddPoint(newValue, newOpacity);
            m_guiUpdateFlags.transferFunctionChanged = true;
            m_wasClicked = true;
        }
    }
}

// For dragging control points
void TransferFunctionGui::HandleDrag()
{
    if (ImGui::IsItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Left, 0.0f) && !m_wasClicked)
    {
        if (!m_draggedPointIndex)
        {
            m_draggedPointIndex = GetNearestPointIndex();
        }

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

std::optional<size_t> TransferFunctionGui::GetNearestPointIndex() const
{
    auto calculateDistance = [&](size_t index)
    {
        const auto& point = m_transferFunction[index];
        const float x = m_plotPos.x + point.value * m_plotSize.x;
        const float y = m_plotPos.y + m_plotSize.y - m_gradientHeight - (point.opacity * m_interactiveAreaHeight);
        return std::sqrt((m_mousePos.x - x) * (m_mousePos.x - x) + (m_mousePos.y - y) * (m_mousePos.y - y));
    };

    auto pointIndices = std::views::iota(size_t{ 0 }, m_numActivePoints);
    auto nearestPointIndex = std::ranges::min_element(pointIndices, {}, calculateDistance);

    if (nearestPointIndex != pointIndices.end() && calculateDistance(*nearestPointIndex) < Constants::interactionRadius)
    {
        return *nearestPointIndex;
    }

    return std::nullopt;
}

void TransferFunctionGui::Draw()
{
    // Set cursor when hovering over a control point
    if (m_hoveredPointIndex && !ImGui::GetIO().KeyShift)
    {
        ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
    }

    ImDrawList* drawList = ImGui::GetWindowDrawList();

    // Draw background
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
    const auto activePoints = std::span{m_transferFunction.GetControlPoints().data(), m_numActivePoints};
    auto gradientIndices = std::views::iota(0, gradientSteps - 1);

    std::ranges::for_each(gradientIndices, [&](int i)
    {
        const float t = static_cast<float>(i) / (gradientSteps - 1);
        const float nextT = static_cast<float>(i + 1) / (gradientSteps - 1);

        const glm::vec4 rgba = InterpolateTransferFunction(t, activePoints);
        const glm::vec3 color = glm::vec3(rgba.r, rgba.g, rgba.b);

        const float x1 = m_plotPos.x + t * m_plotSize.x;
        const float x2 = m_plotPos.x + nextT * m_plotSize.x;
        const float y1 = m_plotPos.y + m_plotSize.y - m_gradientHeight;
        const float y2 = m_plotPos.y + m_plotSize.y;

        const ImU32 col = IM_COL32(static_cast<int>(color.r * 255), static_cast<int>(color.g * 255), static_cast<int>(color.b * 255), 255);
        drawList->AddRectFilled(ImVec2(x1, y1), ImVec2(x2, y2), col);
    });

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
