#include <buffers/FrameBuffer.h>
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
#include <shader/UpdateLightingParametersInShader.h>
#include <shader/UpdateMatricesInShader.h>
#include <shader/UpdateSsaoFinalShader.h>
#include <shader/UpdateSsaoShader.h>
#include <textures/Texture.h>
#include <utils/FileSystem.h>
#include <utils/SsaoUtils.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <numbers>
#include <iostream>

namespace Constants
{
    const glm::mat4 lightSourceCubeScalingMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.2));
}

namespace
{
    // TODO move
    void UpdateSsaoNoiseTexture(const GuiParameters& guiParameters, const SsaoUtils& ssaoUtils, Texture& ssaoNoiseTexture)
    {
        ssaoNoiseTexture = Texture(ssaoNoiseTexture.GetTextureUnitEnum(), guiParameters.ssaoNoiseSize, guiParameters.ssaoNoiseSize, GL_RGBA32F, GL_RGB, GL_FLOAT, GL_NEAREST, GL_REPEAT, ssaoUtils.GetNoise());
    }
}

int main()
{
    // TODO use unique_ptr for window
    auto window = Context::InitGlfw();
    Context::InitGlad();
    Context::InitGl();
    
    DisplayProperties displayProperties = Factory::MakeDisplayProperties();
    GuiParameters guiParameters = Factory::MakeGuiParameters();
    GuiUpdateFlags guiUpdateFlags;

    Shader ssaoInputShader(FileSystem::getPath("src/shaders/SsaoInput.vert").c_str(), FileSystem::getPath("src/shaders/SsaoInput.frag").c_str());
    Shader ssaoShader(FileSystem::getPath("src/shaders/Ssao.vert").c_str(), FileSystem::getPath("src/shaders/Ssao.frag").c_str());
    Shader ssaoBlurShader(FileSystem::getPath("src/shaders/Ssao.vert").c_str(), FileSystem::getPath("src/shaders/SsaoBlur.frag").c_str());
    Shader ssaoFinalShader(FileSystem::getPath("src/shaders/SsaoFinal.vert").c_str(), FileSystem::getPath("src/shaders/SsaoFinal.frag").c_str());
    Shader ssaoDebugQuadShader(FileSystem::getPath("src/shaders/DebugQuad.vert").c_str(), FileSystem::getPath("src/shaders/DebugQuadColor.frag").c_str());
    Shader lightSourceShader(FileSystem::getPath("src/shaders/LightSource.vert").c_str(), FileSystem::getPath("src/shaders/LightSource.frag").c_str());

    SsaoUtils ssaoUtils;
        
    Texture ssaoPositionTexture(GL_TEXTURE1, Config::windowWidth, Config::windowHeight, GL_RGBA16F, GL_RGBA, GL_FLOAT, GL_NEAREST, GL_CLAMP_TO_EDGE);
    Texture ssaoLightSpacePositionTexture(GL_TEXTURE2, Config::windowWidth, Config::windowHeight, GL_RGBA16F, GL_RGBA, GL_FLOAT, GL_NEAREST, GL_CLAMP_TO_EDGE);    
    Texture ssaoNormalTexture(GL_TEXTURE3, Config::windowWidth, Config::windowHeight, GL_RGBA16F, GL_RGBA, GL_FLOAT, GL_NEAREST, GL_REPEAT);
    Texture ssaoAlbedoTexture(GL_TEXTURE4, Config::windowWidth, Config::windowHeight, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, GL_NEAREST, GL_REPEAT);
    Texture ssaoTexture(GL_TEXTURE5, Config::windowWidth, Config::windowHeight, GL_RED, GL_RED, GL_FLOAT, GL_NEAREST, GL_REPEAT);
    Texture ssaoBlurTexture(GL_TEXTURE6, Config::windowWidth, Config::windowHeight, GL_RED, GL_RED, GL_FLOAT, GL_NEAREST, GL_REPEAT);
    Texture ssaoNoiseTexture(GL_TEXTURE7, Config::defaultSsaoNoiseSize, Config::defaultSsaoNoiseSize, GL_RGBA32F, GL_RGB, GL_FLOAT, GL_NEAREST, GL_REPEAT, ssaoUtils.GetNoise());
    Texture ssaoStencilTexture(GL_TEXTURE8, Config::windowWidth, Config::windowHeight, GL_RED, GL_RED, GL_FLOAT, GL_NEAREST, GL_REPEAT);
    Texture ssaoPointLightsContributionTexture(GL_TEXTURE9, Config::windowWidth, Config::windowHeight, GL_RED, GL_RED, GL_FLOAT, GL_NEAREST, GL_REPEAT);

    FrameBuffer ssaoInputFrameBuffer;
    ssaoInputFrameBuffer.Bind();
    ssaoInputFrameBuffer.AttachTexture(GL_COLOR_ATTACHMENT0, ssaoPositionTexture);
    ssaoInputFrameBuffer.AttachTexture(GL_COLOR_ATTACHMENT1, ssaoLightSpacePositionTexture);
    ssaoInputFrameBuffer.AttachTexture(GL_COLOR_ATTACHMENT2, ssaoNormalTexture);
    ssaoInputFrameBuffer.AttachTexture(GL_COLOR_ATTACHMENT3, ssaoAlbedoTexture);
    ssaoInputFrameBuffer.AttachTexture(GL_COLOR_ATTACHMENT4, ssaoPointLightsContributionTexture);
    ssaoInputFrameBuffer.AttachTexture(GL_COLOR_ATTACHMENT5, ssaoStencilTexture);
    unsigned int attachments[6] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3, GL_COLOR_ATTACHMENT4, GL_COLOR_ATTACHMENT5 }; // TODO - move into FrameBuffer
    glDrawBuffers(6, attachments);
    ssaoInputFrameBuffer.AttachRenderBuffer(GL_DEPTH_ATTACHMENT, GL_DEPTH_COMPONENT, Config::windowWidth, Config::windowHeight);
    ssaoInputFrameBuffer.Check();
    ssaoInputFrameBuffer.Unbind();

    FrameBuffer ssaoFrameBuffer;
    ssaoFrameBuffer.Bind();
    ssaoFrameBuffer.AttachTexture(GL_COLOR_ATTACHMENT0, ssaoTexture);
    ssaoFrameBuffer.Check();
    ssaoFrameBuffer.Unbind();

    FrameBuffer ssaoBlurFrameBuffer;
    ssaoBlurFrameBuffer.Bind();
    ssaoBlurFrameBuffer.AttachTexture(GL_COLOR_ATTACHMENT0, ssaoBlurTexture);
    ssaoBlurFrameBuffer.Check();
    ssaoBlurFrameBuffer.Unbind();

    ssaoShader.use();
    ssaoShader.setVec2("windowSize", glm::vec2(Config::windowWidth, Config::windowHeight));
    ssaoShader.setInt("gPosition", ssaoPositionTexture.GetTextureUnit());
    ssaoShader.setInt("gNormal", ssaoNormalTexture.GetTextureUnit());
    ssaoShader.setInt("texNoise", ssaoNoiseTexture.GetTextureUnit());
    ShaderUtils::UpdateSsaoShader(guiParameters, ssaoUtils, ssaoShader);

    ssaoBlurShader.use();
    ssaoBlurShader.setInt("ssaoInput", ssaoTexture.GetTextureUnit());

    ssaoFinalShader.use();
    ssaoFinalShader.setInt("ssaoPosition", ssaoPositionTexture.GetTextureUnit());
    ssaoFinalShader.setInt("ssaoLightSpacePosition", ssaoLightSpacePositionTexture.GetTextureUnit());
    ssaoFinalShader.setInt("ssaoNormal", ssaoNormalTexture.GetTextureUnit());
    ssaoFinalShader.setInt("ssaoAlbedo", ssaoAlbedoTexture.GetTextureUnit());
    ssaoFinalShader.setInt("ssaoPointLightsContribution", ssaoPointLightsContributionTexture.GetTextureUnit());
    ssaoFinalShader.setInt("ssaoMap", ssaoTexture.GetTextureUnit());
    ssaoFinalShader.setInt("enableSsao", guiParameters.enableSsao);

    Camera camera(-2.25293994f, 9.60278416f, -4.95751047f, 0.00000000f, 1.00000000f, 0.00000000f, 389.10012817f, -30.39993668f);
    ScreenQuad screenQuad;
    InputHandler inputHandler(window, camera, displayProperties);
    Gui gui(window, guiParameters, guiUpdateFlags);


    while (!glfwWindowShouldClose(window))
    {
        inputHandler.Update();
        
        if (guiUpdateFlags.ssaoParametersChanged)
        {
            ssaoUtils.UpdateKernel(guiParameters.ssaoKernelSize);
            ssaoUtils.UpdateNoise(guiParameters.ssaoNoiseSize);
            UpdateSsaoNoiseTexture(guiParameters, ssaoUtils, ssaoNoiseTexture);
            ssaoShader.use();
            ShaderUtils::UpdateSsaoShader(guiParameters, ssaoUtils, ssaoShader);
            ssaoFinalShader.use();
            ShaderUtils::UpdateSsaoFinalShader(guiParameters, ssaoFinalShader);
            guiUpdateFlags.ssaoParametersChanged = false;
        }

        const glm::mat4 lightSpaceMatrix = GetLightSpaceMatrix(guiParameters);

        glViewport(0, 0, inputHandler.GetWindowWidth(), inputHandler.GetWindowHeight());
        glDisable(GL_BLEND);

                
        // ------------------------------------------------  SSAO pass 1 (input)
        ssaoInputFrameBuffer.Bind(); 
        ssaoInputShader.use();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ShaderUtils::UpdateMatricesInShader(camera, ssaoInputShader);
        ssaoInputShader.setMat4("lightSpace", lightSpaceMatrix);

        ssaoInputFrameBuffer.Unbind();


        // ------------------------------------------------  SSAO pass 2 (ssao)
        ssaoFrameBuffer.Bind();
        ssaoShader.use();
        ShaderUtils::UpdateMatricesInShader(camera, ssaoShader);
        glClear(GL_COLOR_BUFFER_BIT);
        ssaoPositionTexture.Bind();
        ssaoNormalTexture.Bind();
        ssaoNoiseTexture.Bind();
        screenQuad.Render();
        ssaoFrameBuffer.Unbind();


        // ------------------------------------------------  SSAO pass 3 (blur)
        ssaoBlurFrameBuffer.Bind();
        ssaoBlurShader.use();
        glClear(GL_COLOR_BUFFER_BIT);
        ssaoTexture.Bind();
        screenQuad.Render();
        ssaoBlurFrameBuffer.Unbind();

          
        // ------------------------------------------------  SSAO pass 4 (compositing)        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDepthMask(GL_FALSE);
        ssaoFinalShader.use();
        ShaderUtils::UpdateLightingParametersInShader(guiParameters, ssaoFinalShader);
        ssaoPositionTexture.Bind();
        ssaoLightSpacePositionTexture.Bind();
        ssaoNormalTexture.Bind();
        ssaoAlbedoTexture.Bind();
        ssaoPointLightsContributionTexture.Bind();
        ssaoBlurTexture.Bind();
        screenQuad.Render();
        glDepthMask(GL_TRUE);


        // ------------------------------------------------  copy depth buffer
        ssaoInputFrameBuffer.Bind();
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
        glBlitFramebuffer(0, 0, Config::windowWidth, Config::windowHeight, 0, 0, Config::windowWidth, Config::windowHeight, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
        ssaoInputFrameBuffer.Unbind();


        // ------------------------------------------------  render calls without SSAO
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        if (guiParameters.showLightSources)
        {
            lightSourceShader.use();
            ShaderUtils::UpdateMatricesInShader(camera, lightSourceShader);

            for (unsigned int i = 0; i < Config::numPointLights; ++i)
            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), guiParameters.pointLights[i].position) * Constants::lightSourceCubeScalingMatrix;
                lightSourceShader.setMat4("model", model);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
        }

        // ------------------------------------------------  Debug rendering of SSAO buffers
        if (displayProperties.showSsaoMap)
        {
            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            ssaoDebugQuadShader.use();
            ssaoBlurTexture.Bind();
            ssaoDebugQuadShader.setInt("colorTexture", ssaoBlurTexture.GetTextureUnit());
            ssaoDebugQuadShader.setInt("isSingleChannel", 1);
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
