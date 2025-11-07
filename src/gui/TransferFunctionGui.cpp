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

    if (ImGui::Checkbox("Enable Transfer Function", &guiParameters.transferFunction.enabled))
    {
        guiUpdateFlags.transferFunctionChanged = true;
    }

    ImGui::Separator();

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

    if (isActive && ImGui::IsMouseDragging(ImGuiMouseButton_Left, 0.0f))
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

            drawList->AddLine(ImVec2(x0, y0), ImVec2(x1, y1), IM_COL32(255, 255, 255, 255), 2.0f);
        }
    }

    // Draw control points
    for (size_t i = 0; i < guiParameters.transferFunction.numActivePoints; ++i)
    {
        auto& point = guiParameters.transferFunction.controlPoints[i];
        float x = plotPos.x + point.value * plotSize.x;
        float y = plotPos.y + plotSize.y - gradientHeight - (point.opacity * interactiveAreaHeight);

        // Highlight the dragged point
        bool isDragged = (draggedPointIndex == static_cast<int>(i));
        float radius = isDragged ? 7.0f : 5.0f;
        ImU32 fillColor = isDragged ? IM_COL32(255, 128, 0, 255) : IM_COL32(255, 255, 0, 255);

        drawList->AddCircleFilled(ImVec2(x, y), radius, fillColor);
        drawList->AddCircle(ImVec2(x, y), radius, IM_COL32(0, 0, 0, 255), 12, 2.0f);
    }

    ImGui::Separator();

    ImGui::Separator();

    if (ImGui::Button("Add Control Point") && guiParameters.transferFunction.numActivePoints < TransferFunction::maxControlPoints)
    {
        size_t index = guiParameters.transferFunction.numActivePoints++;
        guiParameters.transferFunction.controlPoints[index].value = 0.5f;
        guiParameters.transferFunction.controlPoints[index].color = glm::vec3(1.0f, 1.0f, 1.0f);
        guiParameters.transferFunction.controlPoints[index].opacity = 1.0f;
        guiUpdateFlags.transferFunctionChanged = true;
    }

    ImGui::SameLine();

    if (ImGui::Button("Remove Last Point") && guiParameters.transferFunction.numActivePoints > 0)
    {
        guiParameters.transferFunction.numActivePoints--;
        guiUpdateFlags.transferFunctionChanged = true;
    }

    ImGui::Text("Active Points: %zu / %zu", guiParameters.transferFunction.numActivePoints, TransferFunction::maxControlPoints);

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
