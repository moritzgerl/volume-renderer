#include <gui/Gui.h>
#include <gui/GuiParameters.h>
#include <gui/GuiUpdateFlags.h>
#include <config/Config.h>

namespace Constants
{
    const ImGuiColorEditFlags colorPickerFlags = ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_Float;
}

Gui::Gui(const Context::WindowPtr& window, GuiParameters& guiParameters, GuiUpdateFlags& guiUpdateFlags)
    : m_window(window)
    , m_guiParameters(guiParameters)
    , m_guiUpdateFlags(guiUpdateFlags)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    //ImGui::StyleColorsDark();
    ImGui::StyleColorsLight();

    ImGui_ImplGlfw_InitForOpenGL(window.get(), true);
    ImGui_ImplOpenGL3_Init("#version 130");
}

void Gui::Shutdown()
{   
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Gui::Draw()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::ShowDemoWindow();

    //ImGui::Begin("SSAO");

    //if (ImGui::SliderInt("Kernel Size", reinterpret_cast<int*>(&m_guiParameters.ssaoKernelSize), 32, 128) ||    // careful, need to adjust max kernel size in Ssao.frag according to the max here
    //    ImGui::SliderInt("Noise Size", reinterpret_cast<int*>(&m_guiParameters.ssaoNoiseSize), 4, 16) ||
    //    ImGui::SliderFloat("Radius", &m_guiParameters.ssaoRadius, 0.0f, 1.0f) ||
    //    ImGui::SliderFloat("Bias", &m_guiParameters.ssaoBias, 0.0f, 0.1f) ||
    //    ImGui::Checkbox("Enable", &m_guiParameters.enableSsao))
    //{
    //    m_guiUpdateFlags.ssaoParametersChanged = true;
    //}    
    //ImGui::End();

    //ImGui::Begin("Lighting");

    //if (ImGui::CollapsingHeader("Directional Light"))
    //{
    //    ImGui::SliderFloat("Direction X", &m_guiParameters.directionalLight.direction.x, -1.0f, 1.0f);
    //    ImGui::SliderFloat("Direction Y", &m_guiParameters.directionalLight.direction.y, -1.0f, 1.0f);
    //    ImGui::SliderFloat("Direction Z", &m_guiParameters.directionalLight.direction.z, -1.0f, 1.0f);
    //    ImGui::SliderFloat("Intensity##0", &m_guiParameters.directionalLight.intensity, 0.0f, 1.0f);

    //    if (ImGui::TreeNode("Ambient"))
    //    {
    //        ImGui::ColorPicker4("Ambient", (float*)&m_guiParameters.directionalLight.ambient, Constants::colorPickerFlags, NULL);
    //    }
    //    if (ImGui::TreeNode("Diffuse"))
    //    {
    //        ImGui::ColorPicker4("Diffuse", (float*)&m_guiParameters.directionalLight.diffuse, Constants::colorPickerFlags, NULL);
    //    }
    //    if (ImGui::TreeNode("Specular"))
    //    {
    //        ImGui::ColorPicker4("Specular", (float*)&m_guiParameters.directionalLight.specular, Constants::colorPickerFlags, NULL);
    //    }
    //}

    //for (unsigned int i = 0; i < Config::numPointLights; ++i)
    //{
    //    const std::string index = std::to_string(i);

    //    if (ImGui::CollapsingHeader(("Point Light " + index).c_str()))
    //    {
    //        ImGui::Checkbox(("Show Light Source##" + index).c_str(), &m_guiParameters.showLightSources);
    //        ImGui::SliderFloat("Position X", &m_guiParameters.pointLights[i].position.x, -32.0f, 32.0f);
    //        ImGui::SliderFloat("Position Y", &m_guiParameters.pointLights[i].position.y, 0.0f, 5.0f);
    //        ImGui::SliderFloat("Position Z", &m_guiParameters.pointLights[i].position.z, -32.0f, 32.0f);
    //        ImGui::SliderFloat(("Intensity##" + index).c_str(), &m_guiParameters.pointLights[i].intensity, 0.0f, 1.0f);

    //        if (ImGui::TreeNode("Ambient"))
    //        {
    //            ImGui::ColorPicker4("Ambient", (float*)&m_guiParameters.pointLights[i].ambient, Constants::colorPickerFlags, NULL);
    //        }
    //        if (ImGui::TreeNode("Diffuse"))
    //        {
    //            ImGui::ColorPicker4("Diffuse", (float*)&m_guiParameters.pointLights[i].diffuse, Constants::colorPickerFlags, NULL);
    //        }
    //        if (ImGui::TreeNode("Specular"))
    //        {
    //            ImGui::ColorPicker4("Specular", (float*)&m_guiParameters.pointLights[i].specular, Constants::colorPickerFlags, NULL);
    //        }
    //    }
    //}
    //ImGui::End();

    ImGui::Begin("Transfer Function");

    if (ImGui::Checkbox("Enable Transfer Function", &m_guiParameters.transferFunction.enabled))
    {
        m_guiUpdateFlags.transferFunctionChanged = true;
    }

    ImGui::Separator();

    // Transfer function plot
    if (m_guiParameters.transferFunction.numActivePoints > 0)
    {
        ImVec2 plotSize(ImGui::GetContentRegionAvail().x, 200.0f);
        ImDrawList* drawList = ImGui::GetWindowDrawList();
        ImVec2 plotPos = ImGui::GetCursorScreenPos();

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
        const float gradientHeight = 20.0f;
        const int gradientSteps = 256;
        for (int i = 0; i < gradientSteps - 1; ++i)
        {
            float t = static_cast<float>(i) / (gradientSteps - 1);
            float nextT = static_cast<float>(i + 1) / (gradientSteps - 1);

            // Find surrounding control points and interpolate color
            glm::vec3 color = glm::vec3(0.5f);
            for (size_t j = 0; j < m_guiParameters.transferFunction.numActivePoints; ++j)
            {
                if (m_guiParameters.transferFunction.controlPoints[j].value >= t)
                {
                    if (j == 0)
                    {
                        color = m_guiParameters.transferFunction.controlPoints[j].color;
                    }
                    else
                    {
                        auto& p0 = m_guiParameters.transferFunction.controlPoints[j - 1];
                        auto& p1 = m_guiParameters.transferFunction.controlPoints[j];
                        float localT = (t - p0.value) / (p1.value - p0.value);
                        color = glm::mix(p0.color, p1.color, localT);
                    }
                    break;
                }
                else if (j == m_guiParameters.transferFunction.numActivePoints - 1)
                {
                    color = m_guiParameters.transferFunction.controlPoints[j].color;
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
        if (m_guiParameters.transferFunction.numActivePoints >= 2)
        {
            for (size_t i = 0; i < m_guiParameters.transferFunction.numActivePoints - 1; ++i)
            {
                auto& p0 = m_guiParameters.transferFunction.controlPoints[i];
                auto& p1 = m_guiParameters.transferFunction.controlPoints[i + 1];

                float x0 = plotPos.x + p0.value * plotSize.x;
                float y0 = plotPos.y + plotSize.y - gradientHeight - (p0.opacity * (plotSize.y - gradientHeight));

                float x1 = plotPos.x + p1.value * plotSize.x;
                float y1 = plotPos.y + plotSize.y - gradientHeight - (p1.opacity * (plotSize.y - gradientHeight));

                drawList->AddLine(ImVec2(x0, y0), ImVec2(x1, y1), IM_COL32(255, 255, 255, 255), 2.0f);
            }
        }

        // Draw control points
        for (size_t i = 0; i < m_guiParameters.transferFunction.numActivePoints; ++i)
        {
            auto& point = m_guiParameters.transferFunction.controlPoints[i];
            float x = plotPos.x + point.value * plotSize.x;
            float y = plotPos.y + plotSize.y - gradientHeight - (point.opacity * (plotSize.y - gradientHeight));

            drawList->AddCircleFilled(ImVec2(x, y), 5.0f, IM_COL32(255, 255, 0, 255));
            drawList->AddCircle(ImVec2(x, y), 5.0f, IM_COL32(0, 0, 0, 255), 12, 2.0f);
        }

        // Reserve space for the plot
        ImGui::Dummy(plotSize);

        ImGui::Separator();
    }

    ImGui::Separator();

    if (ImGui::Button("Add Control Point") && m_guiParameters.transferFunction.numActivePoints < TransferFunction::maxControlPoints)
    {
        size_t index = m_guiParameters.transferFunction.numActivePoints++;
        m_guiParameters.transferFunction.controlPoints[index].value = 0.5f;
        m_guiParameters.transferFunction.controlPoints[index].color = glm::vec3(1.0f, 1.0f, 1.0f);
        m_guiParameters.transferFunction.controlPoints[index].opacity = 1.0f;
        m_guiUpdateFlags.transferFunctionChanged = true;
    }

    ImGui::SameLine();

    if (ImGui::Button("Remove Last Point") && m_guiParameters.transferFunction.numActivePoints > 0)
    {
        m_guiParameters.transferFunction.numActivePoints--;
        m_guiUpdateFlags.transferFunctionChanged = true;
    }

    ImGui::Text("Active Points: %zu / %zu", m_guiParameters.transferFunction.numActivePoints, TransferFunction::maxControlPoints);

    ImGui::Separator();

    for (size_t i = 0; i < m_guiParameters.transferFunction.numActivePoints; ++i)
    {
        const std::string index = std::to_string(i);
        auto& point = m_guiParameters.transferFunction.controlPoints[i];

        if (ImGui::CollapsingHeader(("Control Point " + index).c_str()))
        {
            bool changed = false;

            changed |= ImGui::SliderFloat(("Value##" + index).c_str(), &point.value, 0.0f, 1.0f);
            changed |= ImGui::SliderFloat(("Opacity##" + index).c_str(), &point.opacity, 0.0f, 1.0f);

            if (ImGui::TreeNode(("Color##" + index).c_str()))
            {
                changed |= ImGui::ColorPicker3(("Color Picker##" + index).c_str(), (float*)&point.color, Constants::colorPickerFlags);
                ImGui::TreePop();
            }

            if (changed)
            {
                m_guiUpdateFlags.transferFunctionChanged = true;
            }
        }
    }

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
