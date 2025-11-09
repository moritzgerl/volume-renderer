#include <gui/Gui.h>
#include <config/Config.h>
#include <data/SaveState.h>
#include <gui/GuiParameters.h>
#include <gui/GuiUpdateFlags.h>
#include <gui/MakeCheckbox.h>
#include <gui/MakeSlider.h>
#include <gui/StyleGui.h>
#include <gui/TransferFunctionGui.h>

#include <GLFW/glfw3.h>

namespace Constants
{
    const ImGuiColorEditFlags colorPickerFlags = ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_Float;
}

Gui::Gui(const Context::WindowPtr& window, Data::SaveState& saveState, GuiParameters& guiParameters, GuiUpdateFlags& guiUpdateFlags)
    : m_window(window)
    , m_saveState(saveState)
    , m_guiParameters(guiParameters)
    , m_guiUpdateFlags(guiUpdateFlags)
    , m_guiWidth(0.0f)
    , m_transferFunctionHeight(0.0f)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        
    ImFontConfig fontConfig;
    fontConfig.SizePixels = 16.0f;
    fontConfig.OversampleH = 4;
    fontConfig.OversampleV = 4;
    io.Fonts->AddFontDefault(&fontConfig);

    ImGui::StyleColorsDark();

    StyleGui();

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

    // Trackball
    if (ImGui::CollapsingHeader("Camera", ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow))
    {
        MakeCheckbox("Invert Y Axis", &m_guiParameters.trackballInvertYAxis);

        // TODO make nice
        float normalizedSensitivity = (m_guiParameters.trackballSensitivity - Config::trackballSensitivityMin) / (Config::trackballSensitivityMax - Config::trackballSensitivityMin);
        if (MakeSliderFloat("Sensitivity", &normalizedSensitivity, 0.0f, 1.0f))
        {
            m_guiParameters.trackballSensitivity = Config::trackballSensitivityMin + normalizedSensitivity * (Config::trackballSensitivityMax - Config::trackballSensitivityMin);
        }
    }

    // SSAO
    if (ImGui::CollapsingHeader("SSAO", ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow))
    {
        if (MakeSliderInt("Kernel Size", reinterpret_cast<int*>(&m_guiParameters.ssaoKernelSize), 32, 128) ||
            MakeSliderInt("Noise Size", reinterpret_cast<int*>(&m_guiParameters.ssaoNoiseSize), 4, 16) ||
            MakeSliderFloat("Radius", &m_guiParameters.ssaoRadius, 0.0f, 1.0f) ||
            MakeSliderFloat("Bias", &m_guiParameters.ssaoBias, 0.0f, 0.1f) ||
            MakeCheckbox("Enable", &m_guiParameters.enableSsao))
        {
            m_guiUpdateFlags.ssaoParametersChanged = true;
        }
    }

    // Lighting
    if (ImGui::CollapsingHeader("Lighting", ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow))
    {
        if (ImGui::TreeNode("Directional Light"))
        {
            MakeSliderFloat("Direction X", &m_guiParameters.directionalLight.direction.x, -1.0f, 1.0f);
            MakeSliderFloat("Direction Y", &m_guiParameters.directionalLight.direction.y, -1.0f, 1.0f);
            MakeSliderFloat("Direction Z", &m_guiParameters.directionalLight.direction.z, -1.0f, 1.0f);
            MakeSliderFloat("Intensity", &m_guiParameters.directionalLight.intensity, 0.0f, 1.0f);

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
                MakeCheckbox("Show Light Source", &m_guiParameters.showLightSources);
                MakeSliderFloat("Position X", &m_guiParameters.pointLights[i].position.x, -32.0f, 32.0f);
                MakeSliderFloat("Position Y", &m_guiParameters.pointLights[i].position.y, 0.0f, 5.0f);
                MakeSliderFloat("Position Z", &m_guiParameters.pointLights[i].position.z, -32.0f, 32.0f);
                MakeSliderFloat("Intensity", &m_guiParameters.pointLights[i].intensity, 0.0f, 1.0f);

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

    // Transfer Function
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
        TransferFunctionGui::Draw(m_saveState.transferFunction, m_guiUpdateFlags);
        ImGui::EndChild();

        // Resize handle at the bottom
        ImGui::PushStyleColor(ImGuiCol_Button, bgColor);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.6f, 0.6f, 0.6f, 0.7f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, bgColor);
        ImGui::Button("##TransferFunctionResize", ImVec2(-1, 8.0f));
        bool isResizing = ImGui::IsItemActive();
        ImGui::PopStyleColor(3);

        if (isResizing)
        {
            m_transferFunctionHeight += ImGui::GetIO().MouseDelta.y;

            // Calculate maximum height to prevent pushing content out of window
            // Subtract the space used by the top spacer (8px) from available space
            float maxHeight = availableHeightBeforeTransferFunction - 8.0f;

            m_transferFunctionHeight = std::clamp(m_transferFunctionHeight, 128.0f, maxHeight);

            // Draw 1px blue line when actively resizing (matching ImGui window resize visual)
            ImVec2 buttonMin = ImGui::GetItemRectMin();
            ImVec2 buttonMax = ImGui::GetItemRectMax();
            ImVec2 lineStart = ImVec2(buttonMin.x, buttonMin.y + 4.0f);
            ImVec2 lineEnd = ImVec2(buttonMax.x, buttonMin.y + 4.0f);
            ImVec4 resizeGripColor = ImGui::GetStyleColorVec4(ImGuiCol_ResizeGripActive);
            ImGui::GetWindowDrawList()->AddLine(lineStart, lineEnd, ImGui::ColorConvertFloat4ToU32(resizeGripColor), 1.0f);
        }

        if (ImGui::IsItemHovered())
        {
            ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeNS);
        }
    }

    // Rendering
    if (ImGui::CollapsingHeader("Rendering", ImGuiTreeNodeFlags_DefaultOpen))
    {
        MakeSliderFloat("Opacity", &m_guiParameters.raycastingDensityMultiplier, 5.0f, 40.0f);
    }

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
