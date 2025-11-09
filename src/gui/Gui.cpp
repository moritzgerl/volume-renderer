#include <gui/Gui.h>
#include <gui/GuiParameters.h>
#include <gui/GuiUpdateFlags.h>
#include <gui/TransferFunctionGui.h>
#include <config/Config.h>

#include <GLFW/glfw3.h>

namespace Constants
{
    const ImGuiColorEditFlags colorPickerFlags = ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_Float;
}

Gui::Gui(const Context::WindowPtr& window, GuiParameters& guiParameters, GuiUpdateFlags& guiUpdateFlags)
    : m_window(window)
    , m_guiParameters(guiParameters)
    , m_guiUpdateFlags(guiUpdateFlags)
    , m_guiWidth(0.0f)
    , m_transferFunctionHeight(0.0f)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();

    // Panel header colors
    ImGuiStyle& style = ImGui::GetStyle();
    style.Colors[ImGuiCol_Header] = ImVec4(0.20f, 0.20f, 0.20f, 1.0f);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.0f);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.30f, 0.30f, 0.30f, 1.0f);

    ImGui_ImplGlfw_InitForOpenGL(window.get(), true);
    ImGui_ImplOpenGL3_Init("#version 130");
}

void Gui::Shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

float Gui::GetGuiWidth() const
{
    return m_guiWidth;
}

void Gui::Draw()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Get window dimensions
    int windowWidth, windowHeight;
    glfwGetWindowSize(m_window.get(), &windowWidth, &windowHeight);

    // Calculate initial GUI width and transfer function height based on config
    static bool firstFrame = true;
    if (firstFrame)
    {
        m_guiWidth = static_cast<float>(windowWidth) * Config::defaultGuiWidthRatio;
        m_transferFunctionHeight = static_cast<float>(windowHeight) * Config::defaultTransferFunctionGuiHeightRatio;
        firstFrame = false;
    }

    // Main GUI window - fixed to left side, full height, resizable horizontally
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(m_guiWidth, static_cast<float>(windowHeight)), ImGuiCond_Always);

    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar;

    ImGui::Begin("Settings", nullptr, windowFlags);

    // Update GUI width after potential resize
    m_guiWidth = ImGui::GetWindowWidth();

    // SSAO Panel
    if (ImGui::CollapsingHeader("SSAO", ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow))
    {
        if (ImGui::SliderInt("Kernel Size", reinterpret_cast<int*>(&m_guiParameters.ssaoKernelSize), 32, 128) ||
            ImGui::SliderInt("Noise Size", reinterpret_cast<int*>(&m_guiParameters.ssaoNoiseSize), 4, 16) ||
            ImGui::SliderFloat("Radius", &m_guiParameters.ssaoRadius, 0.0f, 1.0f) ||
            ImGui::SliderFloat("Bias", &m_guiParameters.ssaoBias, 0.0f, 0.1f) ||
            ImGui::Checkbox("Enable", &m_guiParameters.enableSsao))
        {
            m_guiUpdateFlags.ssaoParametersChanged = true;
        }
    }

    // Lighting Panel
    if (ImGui::CollapsingHeader("Lighting", ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow))
    {
        if (ImGui::TreeNode("Directional Light"))
        {
            ImGui::SliderFloat("Direction X", &m_guiParameters.directionalLight.direction.x, -1.0f, 1.0f);
            ImGui::SliderFloat("Direction Y", &m_guiParameters.directionalLight.direction.y, -1.0f, 1.0f);
            ImGui::SliderFloat("Direction Z", &m_guiParameters.directionalLight.direction.z, -1.0f, 1.0f);
            ImGui::SliderFloat("Intensity##0", &m_guiParameters.directionalLight.intensity, 0.0f, 1.0f);

            if (ImGui::TreeNode("Ambient"))
            {
                ImGui::ColorPicker4("Ambient", (float*)&m_guiParameters.directionalLight.ambient, Constants::colorPickerFlags, NULL);
                ImGui::TreePop();
            }
            if (ImGui::TreeNode("Diffuse"))
            {
                ImGui::ColorPicker4("Diffuse", (float*)&m_guiParameters.directionalLight.diffuse, Constants::colorPickerFlags, NULL);
                ImGui::TreePop();
            }
            if (ImGui::TreeNode("Specular"))
            {
                ImGui::ColorPicker4("Specular", (float*)&m_guiParameters.directionalLight.specular, Constants::colorPickerFlags, NULL);
                ImGui::TreePop();
            }
            ImGui::TreePop();
        }

        for (unsigned int i = 0; i < Config::numPointLights; ++i)
        {
            const std::string index = std::to_string(i);

            if (ImGui::TreeNode(("Point Light " + index).c_str()))
            {
                ImGui::Checkbox(("Show Light Source##" + index).c_str(), &m_guiParameters.showLightSources);
                ImGui::SliderFloat("Position X", &m_guiParameters.pointLights[i].position.x, -32.0f, 32.0f);
                ImGui::SliderFloat("Position Y", &m_guiParameters.pointLights[i].position.y, 0.0f, 5.0f);
                ImGui::SliderFloat("Position Z", &m_guiParameters.pointLights[i].position.z, -32.0f, 32.0f);
                ImGui::SliderFloat(("Intensity##" + index).c_str(), &m_guiParameters.pointLights[i].intensity, 0.0f, 1.0f);

                if (ImGui::TreeNode("Ambient"))
                {
                    ImGui::ColorPicker4("Ambient", (float*)&m_guiParameters.pointLights[i].ambient, Constants::colorPickerFlags, NULL);
                    ImGui::TreePop();
                }
                if (ImGui::TreeNode("Diffuse"))
                {
                    ImGui::ColorPicker4("Diffuse", (float*)&m_guiParameters.pointLights[i].diffuse, Constants::colorPickerFlags, NULL);
                    ImGui::TreePop();
                }
                if (ImGui::TreeNode("Specular"))
                {
                    ImGui::ColorPicker4("Specular", (float*)&m_guiParameters.pointLights[i].specular, Constants::colorPickerFlags, NULL);
                    ImGui::TreePop();
                }
                ImGui::TreePop();
            }
        }
    }

    // Transfer Function Panel
    if (ImGui::CollapsingHeader("Transfer Function", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImVec4 bgColor = ImGui::GetStyleColorVec4(ImGuiCol_WindowBg);

        // Measure the space available before resizing
        float availableHeightBeforeTransferFunction = ImGui::GetContentRegionAvail().y;

        // Spacer at the top for symmetry
        ImGui::PushStyleColor(ImGuiCol_Button, bgColor);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, bgColor);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, bgColor);
        ImGui::Button("##TransferFunctionTopSpacer", ImVec2(-1, 8.0f));
        ImGui::PopStyleColor();

        // Child window for the transfer function
        ImGui::BeginChild("TransferFunctionContent", ImVec2(0, m_transferFunctionHeight), true, ImGuiWindowFlags_None);
        TransferFunctionGui::Draw(m_guiParameters, m_guiUpdateFlags);
        ImGui::EndChild();

        // Resize handle at the bottom
        ImGui::PushStyleColor(ImGuiCol_Button, bgColor);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.6f, 0.6f, 0.6f, 0.7f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.8f, 0.8f, 0.8f, 1.0f));
        ImGui::Button("##TransferFunctionResize", ImVec2(-1, 8.0f));
        ImGui::PopStyleColor(3);

        if (ImGui::IsItemActive())
        {
            m_transferFunctionHeight += ImGui::GetIO().MouseDelta.y;

            // Calculate maximum height to prevent pushing content out of window
            // Subtract the space used by the top spacer (8px) from available space
            float maxHeight = availableHeightBeforeTransferFunction - 8.0f;

            m_transferFunctionHeight = std::clamp(m_transferFunctionHeight, 128.0f, maxHeight);
        }

        if (ImGui::IsItemHovered())
        {
            ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeNS);
        }
    }

    if (ImGui::CollapsingHeader("Other", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::Checkbox("Other", &m_guiParameters.showLightSources);
    }

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
