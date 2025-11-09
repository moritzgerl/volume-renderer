#include <gui/MakeSlider.h>

#include <imgui.h>

#include <cstdio>

namespace
{   
    template<typename T, typename SliderFunc>
    // TODO use string
    bool MakeSlider(const char* label, T* value, T min, T max, SliderFunc sliderFunc)
    {
        bool changed = false;

        if (ImGui::BeginTable("##slider_table", 2, ImGuiTableFlags_None))
        {
            ImGui::TableSetupColumn("Label", ImGuiTableColumnFlags_WidthFixed, 120.0f);
            ImGui::TableSetupColumn("Slider", ImGuiTableColumnFlags_WidthStretch);

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::AlignTextToFramePadding();
            ImGui::Text("%s", label);
            ImGui::TableSetColumnIndex(1);

            // TODO don't ;)
            char id[256];
            snprintf(id, sizeof(id), "##%s", label);
            ImGui::SetNextItemWidth(-FLT_MIN);  // use up all available width
            changed = sliderFunc(id, value, min, max, "");

            ImGui::EndTable();
        }

        return changed;
    }
}

bool MakeSliderFloat(const char* label, float* value, float min, float max)
{
    // TODO adjust names
    return MakeSlider(label, value, min, max, [](const char* id, float* v, float mn, float mx, const char* fmt)
    {
        return ImGui::SliderFloat(id, v, mn, mx, fmt);
    });
}

bool MakeSliderInt(const char* label, int* value, int min, int max)
{
    return MakeSlider(label, value, min, max, [](const char* id, int* v, int mn, int mx, const char* fmt)
    {
        return ImGui::SliderInt(id, v, mn, mx, fmt);
    });
}
