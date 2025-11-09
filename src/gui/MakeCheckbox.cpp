#include <gui/MakeCheckbox.h>

#include <imgui.h>

#include <cstdio>

// TODO use string
bool MakeCheckbox(const char* label, bool* value)
{
    bool changed = false;

    if (ImGui::BeginTable("##checkbox_table", 2, ImGuiTableFlags_None))
    {
        ImGui::TableSetupColumn("Label", ImGuiTableColumnFlags_WidthFixed, 120.0f);
        ImGui::TableSetupColumn("Checkbox", ImGuiTableColumnFlags_WidthStretch);

        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::AlignTextToFramePadding();
        ImGui::Text("%s", label);
        ImGui::TableSetColumnIndex(1);

        // TODO don't ;)
        char id[256];
        snprintf(id, sizeof(id), "##%s", label);
        changed = ImGui::Checkbox(id, value);

        ImGui::EndTable();
    }

    return changed;
}
