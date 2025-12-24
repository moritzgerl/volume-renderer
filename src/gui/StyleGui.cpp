#include <gui/StyleGui.h>

#include <imgui.h>

void StyleGui()
{
    ImGuiStyle& style = ImGui::GetStyle();

    // Panel header colors
    style.Colors[ImGuiCol_Header] = ImVec4{0.20f, 0.20f, 0.20f, 1.0f};
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4{0.25f, 0.25f, 0.25f, 1.0f};
    style.Colors[ImGuiCol_HeaderActive] = ImVec4{0.30f, 0.30f, 0.30f, 1.0f};

    // Checkbox colors
    style.Colors[ImGuiCol_CheckMark] = ImVec4{0.90f, 0.90f, 0.90f, 1.0f};        // Brighter checkmark for visibility
    style.Colors[ImGuiCol_FrameBg] = ImVec4{0.20f, 0.20f, 0.20f, 1.0f};          // Checkbox background
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4{0.25f, 0.25f, 0.25f, 1.0f};   // Checkbox background hovered
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4{0.30f, 0.30f, 0.30f, 1.0f};    // Checkbox background active

    // Slider colors
    style.Colors[ImGuiCol_SliderGrab] = ImVec4{0.50f, 0.50f, 0.50f, 1.0f};
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4{0.70f, 0.70f, 0.70f, 1.0f};

    // Button colors
    style.Colors[ImGuiCol_Button] = ImVec4{0.25f, 0.25f, 0.25f, 1.0f};
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4{0.35f, 0.35f, 0.35f, 1.0f};
    style.Colors[ImGuiCol_ButtonActive] = ImVec4{0.45f, 0.45f, 0.45f, 1.0f};

    // Panel header padding
    style.FramePadding = ImVec2{6.0f, 4.0f};
}
