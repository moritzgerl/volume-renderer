#include <buffers/FrameBuffer.h>
#include <buffers/FrameBufferId.h>
#include <config/Config.h>
#include <context/InitGlfw.h>
#include <context/InitGlad.h>
#include <context/InitGl.h>
#include <camera/Camera.h>
#include <input/MakeDisplayProperties.h>
#include <input/DisplayProperties.h>
#include <input/InputHandler.h>
#include <gui/Gui.h>
#include <gui/GuiParameters.h>
#include <gui/GuiUpdateFlags.h>
#include <gui/MakeGuiParameters.h>
#include <lights/GetLightSpaceMatrix.h>
#include <primitives/ScreenQuad.h>
#include <shader/Shader.h>
#include <shader/ShaderId.h>
#include <shader/UpdateLightingParametersInShader.h>
#include <storage/Storage.h>
#include <storage/MakeStorage.h>
#include <shader/UpdateCameraMatricesInShader.h>
#include <shader/UpdateLightSourceModelMatrixInShader.h>
#include <shader/UpdateSsaoFinalShader.h>
#include <shader/UpdateSsaoShader.h>
#include <textures/Texture.h>
#include <textures/TextureId.h>
#include <textures/UpdateSsaoNoiseTexture.h>
#include <utils/SsaoUtils.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <numbers>
#include <iostream>
#include "Main.h"

int main()
{
    // TODO use unique_ptr for window
    auto window = Context::InitGlfw();
    Context::InitGlad();
    Context::InitGl();
    
    DisplayProperties displayProperties = Factory::MakeDisplayProperties();
    GuiParameters guiParameters = Factory::MakeGuiParameters();
    GuiUpdateFlags guiUpdateFlags;
    Gui gui(window, guiParameters, guiUpdateFlags);
    SsaoUtils ssaoUtils;
    Camera camera(-2.25293994f, 9.60278416f, -4.95751047f, 0.00000000f, 1.00000000f, 0.00000000f, 389.10012817f, -30.39993668f);
    InputHandler inputHandler(window, camera, displayProperties);
    ScreenQuad screenQuad;
    const glm::mat4 lightSpaceMatrix = GetLightSpaceMatrix(guiParameters);
    Storage storage(Factory::MakeStorage(camera, displayProperties, guiParameters, lightSpaceMatrix, ssaoUtils, screenQuad));
    Texture& ssaoNoiseTexture = storage.GetTexture(TextureId::SsaoNoise);
    const Shader& ssaoShader = storage.GetShader(ShaderId::Ssao);
    const Shader& ssaoFinalShader = storage.GetShader(ShaderId::SsaoFinal);
    const FrameBuffer& ssaoInputFrameBuffer = storage.GetFrameBuffer(FrameBufferId::SsaoInput);
    const std::vector<RenderPass>& renderPasses = storage.GetRenderPasses();

    while (!glfwWindowShouldClose(window))
    {
        inputHandler.Update();
        
        if (guiUpdateFlags.ssaoParametersChanged)
        {
            ssaoUtils.UpdateKernel(guiParameters.ssaoKernelSize);
            ssaoUtils.UpdateNoise(guiParameters.ssaoNoiseSize);
            TextureUtils::UpdateSsaoNoiseTexture(guiParameters, ssaoUtils, ssaoNoiseTexture);
            ssaoShader.Use();
            ShaderUtils::UpdateSsaoShader(guiParameters, ssaoUtils, ssaoShader);
            ssaoFinalShader.Use();
            ShaderUtils::UpdateSsaoFinalShader(guiParameters, ssaoFinalShader);
            guiUpdateFlags.ssaoParametersChanged = false;
        }

        const glm::mat4 lightSpaceMatrix = GetLightSpaceMatrix(guiParameters);

        glViewport(0, 0, inputHandler.GetWindowWidth(), inputHandler.GetWindowHeight());
        glDisable(GL_BLEND);

        for (const RenderPass& renderPass : renderPasses)
        {
            renderPass.Render();
        }

        // Copy depth buffer
        ssaoInputFrameBuffer.Bind();
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
        glBlitFramebuffer(0, 0, Config::windowWidth, Config::windowHeight, 0, 0, Config::windowWidth, Config::windowHeight, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
        ssaoInputFrameBuffer.Unbind();

        if (displayProperties.showGui)
        {
            gui.Draw();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    gui.Shutdown();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
