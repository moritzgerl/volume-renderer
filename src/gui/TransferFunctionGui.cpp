#include <gui/TransferFunctionGui.h>
#include <gui/GuiUpdateFlags.h>
#include <gui/TransferFunction.h>

#include <imgui.h>
#include <algorithm>
#include <cmath>
#include <string>

namespace
{
    const ImGuiColorEditFlags colorPickerFlags = ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_Float;
}

// TODO refactor
void TransferFunctionGui::Draw(TransferFunction& transferFunction, GuiUpdateFlags& guiUpdateFlags)
{
    const size_t numActivePoints = transferFunction.GetNumActivePoints();

    // Transfer function plot - scale to available height
    ImVec2 plotSize(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y);
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    ImVec2 plotPos = ImGui::GetCursorScreenPos();

    const float gradientHeight = 15.0f;
    const float interactiveAreaHeight = plotSize.y - gradientHeight;

    // Make the plot area interactive
    ImGui::InvisibleButton("TransferFunctionPlot", plotSize);
    bool isHovered = ImGui::IsItemHovered();
    bool isActive = ImGui::IsItemActive();

    // Handle mouse interaction with control points
    static int draggedPointIndex = -1;
    static int colorPickerPointIndex = -1;
    ImVec2 mousePos = ImGui::GetMousePos();

    // Check if hovering over a control point
    int hoveredPointIndex = -1;
    if (isHovered)
    {
        float minDist = 15.0f; // Hover radius
        for (size_t i = 0; i < numActivePoints; ++i)
        {
            auto& point = transferFunction[i];
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

    // Handle double-click to open color picker
    if (isActive && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
    {
        float minDist = 15.0f;
        for (size_t i = 0; i < numActivePoints; ++i)
        {
            auto& point = transferFunction[i];
            float x = plotPos.x + point.value * plotSize.x;
            float y = plotPos.y + plotSize.y - gradientHeight - (point.opacity * interactiveAreaHeight);

            float dist = std::sqrt((mousePos.x - x) * (mousePos.x - x) + (mousePos.y - y) * (mousePos.y - y));
            if (dist < minDist)
            {
                minDist = dist;
                colorPickerPointIndex = static_cast<int>(i);
                break;
            }
        }
    }

    // Handle single click to add new control point or Shift+Click to delete
    static bool wasClicked = false;
    if (isActive && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
    {
        // Check if we clicked near an existing point
        float minDist = 15.0f; // Click radius
        int clickedPointIndex = -1;
        for (size_t i = 0; i < numActivePoints; ++i)
        {
            auto& point = transferFunction[i];
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
            for (size_t j = clickedPointIndex; j < numActivePoints - 1; ++j)
            {
                transferFunction[j] = transferFunction[j + 1];
            }
            transferFunction.SetNumActivePoints(numActivePoints - 1);
            guiUpdateFlags.transferFunctionChanged = true;
            transferFunction.UpdateTextureData();
            wasClicked = true;
        }
        // If we didn't click near an existing point, add a new one
        else if (clickedPointIndex == -1 && numActivePoints < TransferFunctionConstants::maxNumControlPoints)
        {
            // Calculate new point position
            float newValue = std::clamp((mousePos.x - plotPos.x) / plotSize.x, 0.0f, 1.0f);
            float newOpacity = std::clamp(1.0f - ((mousePos.y - plotPos.y) / interactiveAreaHeight), 0.0f, 1.0f);

            // Find the insertion position to keep points sorted by value
            size_t insertIndex = numActivePoints;
            for (size_t j = 0; j < numActivePoints; ++j)
            {
                if (transferFunction[j].value > newValue)
                {
                    insertIndex = j;
                    break;
                }
            }

            // Shift existing points to make room for the new point
            for (size_t j = numActivePoints; j > insertIndex; --j)
            {
                transferFunction[j] = transferFunction[j - 1];
            }

            // Interpolate color from surrounding points
            glm::vec3 newColor = glm::vec3(0.5f);
            if (insertIndex > 0 && insertIndex < numActivePoints)
            {
                // Between two points
                auto& p0 = transferFunction[insertIndex - 1];
                auto& p1 = transferFunction[insertIndex + 1];
                float t = (newValue - p0.value) / (p1.value - p0.value);
                newColor = glm::mix(p0.color, p1.color, t);
            }
            else if (insertIndex == 0 && numActivePoints > 0)
            {
                // Before the first point
                newColor = transferFunction[1].color;
            }
            else if (insertIndex == numActivePoints && numActivePoints > 0)
            {
                // After the last point
                newColor = transferFunction[insertIndex - 1].color;
            }

            // Insert the new point at the correct position
            transferFunction[insertIndex].value = newValue;
            transferFunction[insertIndex].color = newColor;
            transferFunction[insertIndex].opacity = newOpacity;

            transferFunction.IncrementNumActivePoints();

            guiUpdateFlags.transferFunctionChanged = true;
            transferFunction.UpdateTextureData();
            wasClicked = true;
        }
    }

    if (isActive && ImGui::IsMouseDragging(ImGuiMouseButton_Left, 0.0f) && !wasClicked)
    {
        // If we're dragging, find the closest point on first click or continue dragging
        if (draggedPointIndex == -1)
        {
            float minDist = 15.0f; // Click radius
            for (size_t i = 0; i < numActivePoints; ++i)
            {
                auto& point = transferFunction[i];
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
            auto& point = transferFunction[draggedPointIndex];

            // Update value (x-axis) - clamp to prevent crossing adjacent points
            float newValue = (mousePos.x - plotPos.x) / plotSize.x;

            // Get boundaries from adjacent control points
            float minValue = 0.0f;
            float maxValue = 1.0f;

            if (draggedPointIndex > 0)
            {
                minValue = transferFunction[draggedPointIndex - 1].value + 0.001f;
            }

            if (draggedPointIndex < static_cast<int>(numActivePoints) - 1)
            {
                maxValue = transferFunction[draggedPointIndex + 1].value - 0.001f;
            }

            point.value = std::clamp(newValue, minValue, maxValue);

            // Update opacity (y-axis) - clamp to [0, 1]
            float newOpacity = 1.0f - ((mousePos.y - plotPos.y) / interactiveAreaHeight);
            point.opacity = std::clamp(newOpacity, 0.0f, 1.0f);

            guiUpdateFlags.transferFunctionChanged = true;
            transferFunction.UpdateTextureData();
        }
    }
    else
    {
        // Reset dragged point when mouse is released
        draggedPointIndex = -1;
        wasClicked = false;
    }

    // Draw background (transparent)
    drawList->AddRectFilled(plotPos, ImVec2(plotPos.x + plotSize.x, plotPos.y + plotSize.y), IM_COL32(0, 0, 0, 255));

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
        for (size_t j = 0; j < numActivePoints; ++j)
        {
            if (transferFunction[j].value >= t)
            {
                if (j == 0)
                {
                    color = transferFunction[j].color;
                }
                else
                {
                    auto& p0 = transferFunction[j - 1];
                    auto& p1 = transferFunction[j];
                    float localT = (t - p0.value) / (p1.value - p0.value);
                    color = glm::mix(p0.color, p1.color, localT);
                }
                break;
            }
            else if (j == numActivePoints - 1)
            {
                color = transferFunction[j].color;
            }
        }

        float x1 = plotPos.x + t * plotSize.x;
        float x2 = plotPos.x + nextT * plotSize.x;
        float y1 = plotPos.y + plotSize.y - gradientHeight;
        float y2 = plotPos.y + plotSize.y;

        ImU32 col = IM_COL32(static_cast<int>(color.r * 255), static_cast<int>(color.g * 255), static_cast<int>(color.b * 255), 255);
        drawList->AddRectFilled(ImVec2(x1, y1), ImVec2(x2, y2), col);
    }

    // Draw opacity curve with Catmull-Rom spline interpolation
    if (numActivePoints >= 2)
    {
        const int segmentsPerInterval = 20;

        for (size_t i = 0; i < numActivePoints - 1; ++i)
        {
            // Get control points for Catmull-Rom spline
            // Use edge points for extrapolation at boundaries
            auto& p0 = (i == 0) ? transferFunction[0] : transferFunction[i - 1];
            auto& p1 = transferFunction[i];
            auto& p2 = transferFunction[i + 1];
            auto& p3 = (i + 2 >= numActivePoints) ? transferFunction[i + 1] : transferFunction[i + 2];

            // Draw segments between p1 and p2
            for (int seg = 0; seg < segmentsPerInterval; ++seg)
            {
                float t0 = static_cast<float>(seg) / segmentsPerInterval;
                float t1 = static_cast<float>(seg + 1) / segmentsPerInterval;

                // Catmull-Rom spline interpolation
                auto catmullRom = [](float t, float p0, float p1, float p2, float p3) -> float {
                    float t2 = t * t;
                    float t3 = t2 * t;
                    return 0.5f * ((2.0f * p1) +
                        (-p0 + p2) * t +
                        (2.0f * p0 - 5.0f * p1 + 4.0f * p2 - p3) * t2 +
                        (-p0 + 3.0f * p1 - 3.0f * p2 + p3) * t3);
                };

                float opacity0 = catmullRom(t0, p0.opacity, p1.opacity, p2.opacity, p3.opacity);
                float opacity1 = catmullRom(t1, p0.opacity, p1.opacity, p2.opacity, p3.opacity);
                float value0 = p1.value + t0 * (p2.value - p1.value);
                float value1 = p1.value + t1 * (p2.value - p1.value);

                float x0 = plotPos.x + value0 * plotSize.x;
                float y0 = plotPos.y + plotSize.y - gradientHeight - (opacity0 * (plotSize.y - gradientHeight));
                float x1 = plotPos.x + value1 * plotSize.x;
                float y1 = plotPos.y + plotSize.y - gradientHeight - (opacity1 * (plotSize.y - gradientHeight));

                drawList->AddLine(ImVec2(x0, y0), ImVec2(x1, y1), IM_COL32(255, 255, 255, 200), 1.8f);
            }
        }
    }

    // Draw control points
    for (size_t i = 0; i < numActivePoints; ++i)
    {
        auto& point = transferFunction[i];
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
    if (colorPickerPointIndex != -1 && colorPickerPointIndex < static_cast<int>(numActivePoints))
    {
        ImGui::OpenPopup("ColorPickerPopup");
    }

    if (ImGui::BeginPopup("ColorPickerPopup"))
    {
        if (colorPickerPointIndex != -1 && colorPickerPointIndex < static_cast<int>(numActivePoints))
        {
            auto& point = transferFunction[colorPickerPointIndex];
            ImGui::Text("Control Point %d Color", colorPickerPointIndex);
            if (ImGui::ColorPicker3("##picker", (float*)&point.color, colorPickerFlags))
            {
                guiUpdateFlags.transferFunctionChanged = true;
                transferFunction.UpdateTextureData();
            }
            if (ImGui::Button("Close") || ImGui::IsKeyPressed(ImGuiKey_Escape))
            {
                colorPickerPointIndex = -1;
                ImGui::CloseCurrentPopup();
            }
        }
        ImGui::EndPopup();
    }
    else
    {
        // Reset if popup was closed by clicking outside
        if (colorPickerPointIndex != -1 && !ImGui::IsPopupOpen("ColorPickerPopup"))
        {
            colorPickerPointIndex = -1;
        }
    }
}
