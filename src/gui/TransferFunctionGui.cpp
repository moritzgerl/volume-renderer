#include <gui/TransferFunctionGui.h>
#include <gui/GuiParameters.h>
#include <gui/GuiUpdateFlags.h>
#include <gui/TransferFunction.h>

#include <imgui.h>
#include <algorithm>
#include <cmath>
#include <string>

namespace
{
    const ImGuiColorEditFlags colorPickerFlags = ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_Float;
} // anonymous namespace

void TransferFunctionGui::Draw(GuiParameters& guiParameters, GuiUpdateFlags& guiUpdateFlags)
{
    ImGui::Begin("Transfer Function");

    // Transfer function plot
    ImVec2 plotSize(ImGui::GetContentRegionAvail().x, 200.0f);
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    ImVec2 plotPos = ImGui::GetCursorScreenPos();

    const float gradientHeight = 20.0f;
    const float interactiveAreaHeight = plotSize.y - gradientHeight;

    // Make the plot area interactive
    ImGui::InvisibleButton("TransferFunctionPlot", plotSize);
    bool isHovered = ImGui::IsItemHovered();
    bool isActive = ImGui::IsItemActive();

    // Handle mouse interaction with control points
    static int draggedPointIndex = -1;
    ImVec2 mousePos = ImGui::GetMousePos();

    // Check if hovering over a control point
    int hoveredPointIndex = -1;
    if (isHovered)
    {
        float minDist = 15.0f; // Hover radius
        for (size_t i = 0; i < guiParameters.transferFunction.numActivePoints; ++i)
        {
            auto& point = guiParameters.transferFunction.controlPoints[i];
            float x = plotPos.x + point.value * plotSize.x;
            float y = plotPos.y + plotSize.y - gradientHeight - (point.opacity * interactiveAreaHeight);

            float dist = std::sqrt((mousePos.x - x) * (mousePos.x - x) + (mousePos.y - y) * (mousePos.y - y));
            if (dist < minDist)
            {
                minDist = dist;
                hoveredPointIndex = static_cast<int>(i);
            }
        }
    }

    // Set cursor when hovering over a control point
    if (hoveredPointIndex != -1 && !ImGui::GetIO().KeyShift)
    {
        ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
    }

    // Handle single click to add new control point or Shift+Click to delete
    static bool wasClicked = false;
    if (isActive && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
    {
        // Check if we clicked near an existing point
        float minDist = 15.0f; // Click radius
        int clickedPointIndex = -1;
        for (size_t i = 0; i < guiParameters.transferFunction.numActivePoints; ++i)
        {
            auto& point = guiParameters.transferFunction.controlPoints[i];
            float x = plotPos.x + point.value * plotSize.x;
            float y = plotPos.y + plotSize.y - gradientHeight - (point.opacity * interactiveAreaHeight);

            float dist = std::sqrt((mousePos.x - x) * (mousePos.x - x) + (mousePos.y - y) * (mousePos.y - y));
            if (dist < minDist)
            {
                minDist = dist;
                clickedPointIndex = static_cast<int>(i);
            }
        }

        // If Shift is held and we clicked on a point, delete it
        if (ImGui::GetIO().KeyShift && clickedPointIndex != -1)
        {
            // Shift remaining points down
            for (size_t j = clickedPointIndex; j < guiParameters.transferFunction.numActivePoints - 1; ++j)
            {
                guiParameters.transferFunction.controlPoints[j] = guiParameters.transferFunction.controlPoints[j + 1];
            }
            guiParameters.transferFunction.numActivePoints--;
            guiUpdateFlags.transferFunctionChanged = true;
            wasClicked = true;
        }
        // If we didn't click near an existing point, add a new one
        else if (clickedPointIndex == -1 && guiParameters.transferFunction.numActivePoints < TransferFunction::maxControlPoints)
        {
            // Calculate new point position
            float newValue = std::clamp((mousePos.x - plotPos.x) / plotSize.x, 0.0f, 1.0f);
            float newOpacity = std::clamp(1.0f - ((mousePos.y - plotPos.y) / interactiveAreaHeight), 0.0f, 1.0f);

            // Find the insertion position to keep points sorted by value
            size_t insertIndex = guiParameters.transferFunction.numActivePoints;
            for (size_t j = 0; j < guiParameters.transferFunction.numActivePoints; ++j)
            {
                if (guiParameters.transferFunction.controlPoints[j].value > newValue)
                {
                    insertIndex = j;
                    break;
                }
            }

            // Shift existing points to make room for the new point
            for (size_t j = guiParameters.transferFunction.numActivePoints; j > insertIndex; --j)
            {
                guiParameters.transferFunction.controlPoints[j] = guiParameters.transferFunction.controlPoints[j - 1];
            }

            // Interpolate color from surrounding points
            glm::vec3 newColor = glm::vec3(0.5f);
            if (insertIndex > 0 && insertIndex < guiParameters.transferFunction.numActivePoints)
            {
                // Between two points
                auto& p0 = guiParameters.transferFunction.controlPoints[insertIndex - 1];
                auto& p1 = guiParameters.transferFunction.controlPoints[insertIndex + 1];
                float t = (newValue - p0.value) / (p1.value - p0.value);
                newColor = glm::mix(p0.color, p1.color, t);
            }
            else if (insertIndex == 0 && guiParameters.transferFunction.numActivePoints > 0)
            {
                // Before the first point
                newColor = guiParameters.transferFunction.controlPoints[1].color;
            }
            else if (insertIndex == guiParameters.transferFunction.numActivePoints && guiParameters.transferFunction.numActivePoints > 0)
            {
                // After the last point
                newColor = guiParameters.transferFunction.controlPoints[insertIndex - 1].color;
            }

            // Insert the new point at the correct position
            guiParameters.transferFunction.controlPoints[insertIndex].value = newValue;
            guiParameters.transferFunction.controlPoints[insertIndex].color = newColor;
            guiParameters.transferFunction.controlPoints[insertIndex].opacity = newOpacity;

            guiParameters.transferFunction.numActivePoints++;

            guiUpdateFlags.transferFunctionChanged = true;
            wasClicked = true;
        }
    }

    if (isActive && ImGui::IsMouseDragging(ImGuiMouseButton_Left, 0.0f) && !wasClicked)
    {
        // If we're dragging, find the closest point on first click or continue dragging
        if (draggedPointIndex == -1)
        {
            float minDist = 15.0f; // Click radius
            for (size_t i = 0; i < guiParameters.transferFunction.numActivePoints; ++i)
            {
                auto& point = guiParameters.transferFunction.controlPoints[i];
                float x = plotPos.x + point.value * plotSize.x;
                float y = plotPos.y + plotSize.y - gradientHeight - (point.opacity * interactiveAreaHeight);

                float dist = std::sqrt((mousePos.x - x) * (mousePos.x - x) + (mousePos.y - y) * (mousePos.y - y));
                if (dist < minDist)
                {
                    minDist = dist;
                    draggedPointIndex = static_cast<int>(i);
                }
            }
        }

        // Update the dragged point
        if (draggedPointIndex >= 0)
        {
            auto& point = guiParameters.transferFunction.controlPoints[draggedPointIndex];

            // Update value (x-axis) - clamp to [0, 1]
            float newValue = (mousePos.x - plotPos.x) / plotSize.x;
            point.value = std::clamp(newValue, 0.0f, 1.0f);

            // Update opacity (y-axis) - clamp to [0, 1]
            float newOpacity = 1.0f - ((mousePos.y - plotPos.y) / interactiveAreaHeight);
            point.opacity = std::clamp(newOpacity, 0.0f, 1.0f);

            guiUpdateFlags.transferFunctionChanged = true;
        }
    }
    else
    {
        // Reset dragged point when mouse is released
        draggedPointIndex = -1;
        wasClicked = false;
    }

    // Draw background
    drawList->AddRectFilled(plotPos, ImVec2(plotPos.x + plotSize.x, plotPos.y + plotSize.y), IM_COL32(40, 40, 40, 255));

    // Draw grid lines
    for (int i = 0; i <= 10; ++i)
    {
        float y = plotPos.y + (plotSize.y / 10.0f) * i;
        drawList->AddLine(ImVec2(plotPos.x, y), ImVec2(plotPos.x + plotSize.x, y), IM_COL32(80, 80, 80, 100));

        float x = plotPos.x + (plotSize.x / 10.0f) * i;
        drawList->AddLine(ImVec2(x, plotPos.y), ImVec2(x, plotPos.y + plotSize.y), IM_COL32(80, 80, 80, 100));
    }

    // Draw color gradient at the bottom
    const int gradientSteps = 256;
    for (int i = 0; i < gradientSteps - 1; ++i)
    {
        float t = static_cast<float>(i) / (gradientSteps - 1);
        float nextT = static_cast<float>(i + 1) / (gradientSteps - 1);

        // Find surrounding control points and interpolate color
        glm::vec3 color = glm::vec3(0.5f);
        for (size_t j = 0; j < guiParameters.transferFunction.numActivePoints; ++j)
        {
            if (guiParameters.transferFunction.controlPoints[j].value >= t)
            {
                if (j == 0)
                {
                    color = guiParameters.transferFunction.controlPoints[j].color;
                }
                else
                {
                    auto& p0 = guiParameters.transferFunction.controlPoints[j - 1];
                    auto& p1 = guiParameters.transferFunction.controlPoints[j];
                    float localT = (t - p0.value) / (p1.value - p0.value);
                    color = glm::mix(p0.color, p1.color, localT);
                }
                break;
            }
            else if (j == guiParameters.transferFunction.numActivePoints - 1)
            {
                color = guiParameters.transferFunction.controlPoints[j].color;
            }
        }

        float x1 = plotPos.x + t * plotSize.x;
        float x2 = plotPos.x + nextT * plotSize.x;
        float y1 = plotPos.y + plotSize.y - gradientHeight;
        float y2 = plotPos.y + plotSize.y;

        ImU32 col = IM_COL32(static_cast<int>(color.r * 255), static_cast<int>(color.g * 255), static_cast<int>(color.b * 255), 255);
        drawList->AddRectFilled(ImVec2(x1, y1), ImVec2(x2, y2), col);
    }

    // Draw opacity curve
    if (guiParameters.transferFunction.numActivePoints >= 2)
    {
        for (size_t i = 0; i < guiParameters.transferFunction.numActivePoints - 1; ++i)
        {
            auto& p0 = guiParameters.transferFunction.controlPoints[i];
            auto& p1 = guiParameters.transferFunction.controlPoints[i + 1];

            float x0 = plotPos.x + p0.value * plotSize.x;
            float y0 = plotPos.y + plotSize.y - gradientHeight - (p0.opacity * (plotSize.y - gradientHeight));

            float x1 = plotPos.x + p1.value * plotSize.x;
            float y1 = plotPos.y + plotSize.y - gradientHeight - (p1.opacity * (plotSize.y - gradientHeight));

            drawList->AddLine(ImVec2(x0, y0), ImVec2(x1, y1), IM_COL32(255, 255, 255, 200), 1.8f);
        }
    }

    // Draw control points
    for (size_t i = 0; i < guiParameters.transferFunction.numActivePoints; ++i)
    {
        auto& point = guiParameters.transferFunction.controlPoints[i];
        float x = plotPos.x + point.value * plotSize.x;
        float y = plotPos.y + plotSize.y - gradientHeight - (point.opacity * interactiveAreaHeight);

        // Determine color and size based on state
        bool isDragged = (draggedPointIndex == static_cast<int>(i));
        bool isHoveredForDelete = (hoveredPointIndex == static_cast<int>(i) && ImGui::GetIO().KeyShift);

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
            fillColor = IM_COL32(255, 255, 255, 200); // White for normal
        }

        drawList->AddCircleFilled(ImVec2(x, y), radius, fillColor);
        drawList->AddCircle(ImVec2(x, y), radius, IM_COL32(0, 0, 0, 200), 12, 1.0f);
    }

    ImGui::Separator();

    for (size_t i = 0; i < guiParameters.transferFunction.numActivePoints; ++i)
    {
        const std::string index = std::to_string(i);
        auto& point = guiParameters.transferFunction.controlPoints[i];

        if (ImGui::CollapsingHeader(("Control Point " + index).c_str()))
        {
            bool changed = false;

            changed |= ImGui::SliderFloat(("Value##" + index).c_str(), &point.value, 0.0f, 1.0f);
            changed |= ImGui::SliderFloat(("Opacity##" + index).c_str(), &point.opacity, 0.0f, 1.0f);

            if (ImGui::TreeNode(("Color##" + index).c_str()))
            {
                changed |= ImGui::ColorPicker3(("Color Picker##" + index).c_str(), (float*)&point.color, colorPickerFlags);
                ImGui::TreePop();
            }

            if (changed)
            {
                guiUpdateFlags.transferFunctionChanged = true;
            }
        }
    }

    ImGui::End();
}
