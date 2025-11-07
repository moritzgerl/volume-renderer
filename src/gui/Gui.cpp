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

    ImGui::Begin("SSAO");

    if (ImGui::SliderInt("Kernel Size", reinterpret_cast<int*>(&m_guiParameters.ssaoKernelSize), 32, 128) ||    // careful, need to adjust max kernel size in Ssao.frag according to the max here
        ImGui::SliderInt("Noise Size", reinterpret_cast<int*>(&m_guiParameters.ssaoNoiseSize), 4, 16) ||
        ImGui::SliderFloat("Radius", &m_guiParameters.ssaoRadius, 0.0f, 1.0f) ||
        ImGui::SliderFloat("Bias", &m_guiParameters.ssaoBias, 0.0f, 0.1f) ||
        ImGui::Checkbox("Enable", &m_guiParameters.enableSsao))
    {
        m_guiUpdateFlags.ssaoParametersChanged = true;
    }    
    ImGui::End();

    ImGui::Begin("Lighting");

    if (ImGui::CollapsingHeader("Directional Light"))
    {
        ImGui::SliderFloat("Direction X", &m_guiParameters.directionalLight.direction.x, -1.0f, 1.0f);
        ImGui::SliderFloat("Direction Y", &m_guiParameters.directionalLight.direction.y, -1.0f, 1.0f);
        ImGui::SliderFloat("Direction Z", &m_guiParameters.directionalLight.direction.z, -1.0f, 1.0f);
        ImGui::SliderFloat("Intensity##0", &m_guiParameters.directionalLight.intensity, 0.0f, 1.0f);

        if (ImGui::TreeNode("Ambient"))
        {
            ImGui::ColorPicker4("Ambient", (float*)&m_guiParameters.directionalLight.ambient, Constants::colorPickerFlags, NULL);
        }
        if (ImGui::TreeNode("Diffuse"))
        {
            ImGui::ColorPicker4("Diffuse", (float*)&m_guiParameters.directionalLight.diffuse, Constants::colorPickerFlags, NULL);
        }
        if (ImGui::TreeNode("Specular"))
        {
            ImGui::ColorPicker4("Specular", (float*)&m_guiParameters.directionalLight.specular, Constants::colorPickerFlags, NULL);
        }
    }

    for (unsigned int i = 0; i < Config::numPointLights; ++i)
    {
        const std::string index = std::to_string(i);

        if (ImGui::CollapsingHeader(("Point Light " + index).c_str()))
        {
            ImGui::Checkbox(("Show Light Source##" + index).c_str(), &m_guiParameters.showLightSources);
            ImGui::SliderFloat("Position X", &m_guiParameters.pointLights[i].position.x, -32.0f, 32.0f);
            ImGui::SliderFloat("Position Y", &m_guiParameters.pointLights[i].position.y, 0.0f, 5.0f);
            ImGui::SliderFloat("Position Z", &m_guiParameters.pointLights[i].position.z, -32.0f, 32.0f);
            ImGui::SliderFloat(("Intensity##" + index).c_str(), &m_guiParameters.pointLights[i].intensity, 0.0f, 1.0f);

            if (ImGui::TreeNode("Ambient"))
            {
                ImGui::ColorPicker4("Ambient", (float*)&m_guiParameters.pointLights[i].ambient, Constants::colorPickerFlags, NULL);
            }
            if (ImGui::TreeNode("Diffuse"))
            {
                ImGui::ColorPicker4("Diffuse", (float*)&m_guiParameters.pointLights[i].diffuse, Constants::colorPickerFlags, NULL);
            }
            if (ImGui::TreeNode("Specular"))
            {
                ImGui::ColorPicker4("Specular", (float*)&m_guiParameters.pointLights[i].specular, Constants::colorPickerFlags, NULL);
            }
        }
    }
    ImGui::End();

    ImGui::Begin("Transfer Function");

    if (ImGui::Checkbox("Enable Transfer Function", &m_guiParameters.transferFunction.enabled))
    {
        m_guiUpdateFlags.transferFunctionChanged = true;
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
