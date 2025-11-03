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

    const Texture& ssaoPositionTexture = storage.GetTexture(TextureId::SsaoPosition);
    const Texture& ssaoLightSpacePositionTexture = storage.GetTexture(TextureId::SsaoLightSpacePosition);
    const Texture& ssaoNormalTexture = storage.GetTexture(TextureId::SsaoNormal);
    const Texture& ssaoAlbedoTexture = storage.GetTexture(TextureId::SsaoAlbedo);
    const Texture& ssaoTexture = storage.GetTexture(TextureId::Ssao);
    const Texture& ssaoBlurTexture = storage.GetTexture(TextureId::SsaoBlur);
          Texture& ssaoNoiseTexture = storage.GetTexture(TextureId::SsaoNoise);
    const Texture& ssaoStencilTexture = storage.GetTexture(TextureId::SsaoStencil);
    const Texture& ssaoPointLightsContributionTexture = storage.GetTexture(TextureId::SsaoPointLightsContribution);

    const Shader& ssaoInputShader = storage.GetShader(ShaderId::SsaoInput);
    const Shader& ssaoShader = storage.GetShader(ShaderId::Ssao);
    const Shader& ssaoBlurShader = storage.GetShader(ShaderId::SsaoBlur);
    const Shader& ssaoFinalShader = storage.GetShader(ShaderId::SsaoFinal);
    const Shader& ssaoDebugQuadShader = storage.GetShader(ShaderId::DebugQuad);
    const Shader& lightSourceShader = storage.GetShader(ShaderId::LightSource);

    const FrameBuffer& ssaoInputFrameBuffer = storage.GetFrameBuffer(FrameBufferId::SsaoInput);
    const FrameBuffer& ssaoFrameBuffer = storage.GetFrameBuffer(FrameBufferId::Ssao);
    const FrameBuffer& ssaoBlurFrameBuffer = storage.GetFrameBuffer(FrameBufferId::SsaoBlur);

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

                
        // SSAO pass 1 (input)
        ssaoInputFrameBuffer.Bind();
        ssaoInputShader.Use();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ShaderUtils::UpdateCameraMatricesInShader(camera, ssaoInputShader);
        ssaoInputShader.SetMat4("lightSpace", lightSpaceMatrix);
        // TODO render something
        ssaoInputFrameBuffer.Unbind();


        // SSAO pass 2 (ssao)
        ssaoFrameBuffer.Bind();
        ssaoShader.Use();
        ShaderUtils::UpdateCameraMatricesInShader(camera, ssaoShader);
        glClear(GL_COLOR_BUFFER_BIT);
        ssaoPositionTexture.Bind();
        ssaoNormalTexture.Bind();
        ssaoNoiseTexture.Bind();
        screenQuad.Render();
        ssaoFrameBuffer.Unbind();


        // SSAO pass 3 (blur)
        ssaoBlurFrameBuffer.Bind();
        ssaoBlurShader.Use();
        glClear(GL_COLOR_BUFFER_BIT);
        ssaoTexture.Bind();
        screenQuad.Render();
        ssaoBlurFrameBuffer.Unbind();

          
        // SSAO pass 4 (compositing)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDepthMask(GL_FALSE);
        ssaoFinalShader.Use();
        ShaderUtils::UpdateLightingParametersInShader(guiParameters, ssaoFinalShader);
        ssaoPositionTexture.Bind();
        ssaoLightSpacePositionTexture.Bind();
        ssaoNormalTexture.Bind();
        ssaoAlbedoTexture.Bind();
        ssaoPointLightsContributionTexture.Bind();
        ssaoBlurTexture.Bind();
        screenQuad.Render();
        glDepthMask(GL_TRUE);


        // Copy depth buffer
        ssaoInputFrameBuffer.Bind();
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
        glBlitFramebuffer(0, 0, Config::windowWidth, Config::windowHeight, 0, 0, Config::windowWidth, Config::windowHeight, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
        ssaoInputFrameBuffer.Unbind();


        // Render calls without SSAO
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        if (guiParameters.showLightSources)
        {
            lightSourceShader.Use();
            ShaderUtils::UpdateCameraMatricesInShader(camera, lightSourceShader);

            for (unsigned int i = 0; i < Config::numPointLights; ++i)
            {
                ShaderUtils::UpdateLightSourceModelMatrixInShader(guiParameters.pointLights[i].position, lightSourceShader);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
        }

        // Debug rendering of SSAO buffers
        if (displayProperties.showSsaoMap)
        {
            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            ssaoDebugQuadShader.Use();
            ssaoBlurTexture.Bind();
            ssaoDebugQuadShader.SetInt("colorTexture", ssaoBlurTexture.GetTextureUnit());
            ssaoDebugQuadShader.SetInt("isSingleChannel", 1);
            screenQuad.Render();
        }

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
