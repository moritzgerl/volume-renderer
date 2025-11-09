#include <gui/StyleGui.h>

#include <imgui.h>

void StyleGui()
{
    // Panel header colors
    ImGuiStyle& style = ImGui::GetStyle();
    style.Colors[ImGuiCol_Header] = ImVec4(0.20f, 0.20f, 0.20f, 1.0f);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.0f);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.30f, 0.30f, 0.30f, 1.0f);

    // Panel header padding
    style.FramePadding = ImVec2(6.0f, 4.0f);
}
