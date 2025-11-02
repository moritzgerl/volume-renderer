#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <buffers/FrameBuffer.h>
#include <buffers/VertexBuffer.h>
#include <config/Config.h>
#include <camera/Camera.h>
#include <input/MakeDisplayProperties.h>
#include <input/DisplayProperties.h>
#include <input/InputHandler.h>
#include <gui/Gui.h>
#include <gui/GuiParameters.h>
#include <gui/GuiUpdateFlags.h>
#include <gui/MakeGuiParameters.h>
#include <textures/Texture.h>
#include <utils/FileSystem.h>
#include <utils/Shader.h>
#include <utils/SsaoUtils.h>
#include <utils/UnitPlane.h>

#include <numbers>
#include <iostream>

namespace Constants
{
    const glm::mat4 lightSourceCubeScalingMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.2));
}

namespace
{
    // TODO move
    GLFWwindow* InitGlfw()
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        GLFWwindow* window = glfwCreateWindow(Config::windowWidth, Config::windowHeight, "veda", NULL, NULL);
        //GLFWwindow* window = glfwCreateWindow(Config::windowWidth, Config::windowHeight, "veda", glfwGetPrimaryMonitor(), NULL);
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
        }
        glfwMakeContextCurrent(window);

        return window;
    }

    // TODO move
    void InitGlad()
    {
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
        }
    }

    // TODO move
    void InitGl()
    {
        glEnable(GL_PROGRAM_POINT_SIZE);
        glEnable(GL_DEPTH_TEST);
        //glEnable(GL_BLEND);
        //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        //glEnable(GL_CULL_FACE); // OPTIMIZE enable culling, but need to fix normals of unit cube first
        //glCullFace(GL_BACK);
    }


    // TODO - move
    // renderQuad() renders a 1x1 XY quad in NDC
    // -----------------------------------------
    unsigned int quadVAO = 0;
    unsigned int quadVBO;
    void RenderQuad()
    {
        if (quadVAO == 0)
        {
            float quadVertices[] = {
                // positions        // texture Coords
                -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
                -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
                 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
                 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
            };
            // setup plane VAO
            glGenVertexArrays(1, &quadVAO);
            glGenBuffers(1, &quadVBO);
            glBindVertexArray(quadVAO);
            glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        }
        glBindVertexArray(quadVAO);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glBindVertexArray(0);
    }

    // TODO rename
    void UpdateMatricesInShader(const Camera& camera, Shader& shader)
    {
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), static_cast<float>(Config::windowWidth) / static_cast<float>(Config::windowHeight), 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 model = glm::mat4(1.0f);

        shader.setMat4("projection", projection);
        shader.setMat4("view", view);
        shader.setMat4("model", model);
    }

    // TODO move
    void UpdateLightingParametersInShader(const GuiParameters& guiParameters, Shader& shader)
    {
        shader.setVec3("directionalLight.direction", guiParameters.directionalLight.direction);
        shader.setVec3("directionalLight.ambient", guiParameters.directionalLight.ambient);
        shader.setVec3("directionalLight.diffuse", guiParameters.directionalLight.diffuse);
        shader.setVec3("directionalLight.specular", guiParameters.directionalLight.specular);
        shader.setFloat("directionalLight.intensity", guiParameters.directionalLight.intensity);

        for (unsigned int i = 0; i < Config::numPointLights; ++i)
        {
            const std::string name = "pointLights[" + std::to_string(i) + "]";

            shader.setVec3(name + ".position", guiParameters.pointLights[i].position);
            shader.setVec3(name + ".ambient", guiParameters.pointLights[i].ambient);
            shader.setVec3(name + ".diffuse", guiParameters.pointLights[i].diffuse);
            shader.setVec3(name + ".specular", guiParameters.pointLights[i].specular);
            shader.setFloat(name + ".intensity", guiParameters.pointLights[i].intensity);
        }

        shader.setVec3("material.specular", 1.0f, 1.0f, 1.0f);
        shader.setFloat("material.shininess", 1.0f);
    }

    // TODO move
    void UpdateLightingParametersInShader(const Camera& camera, const GuiParameters& guiParameters, Shader& shader)
    {
        shader.setVec3("viewPosition", camera.Position);
        UpdateLightingParametersInShader(guiParameters, shader);
    }

    // TODO move
    void UpdateLightingParametersInShader(const Camera& camera, const glm::mat4& lightSpaceMatrix, const GuiParameters& guiParameters, Shader& shader)
    {
        shader.setVec3("viewPosition", camera.Position);
        shader.setMat4("lightSpace", lightSpaceMatrix);
        UpdateLightingParametersInShader(guiParameters, shader);
    }

    // TODO move
    void UpdateSsaoShader(const GuiParameters& guiParameters, const SsaoUtils& ssaoUtils, Shader& ssaoShader)
    {
        ssaoShader.setInt("kernelSize", guiParameters.ssaoKernelSize);
        ssaoShader.setInt("noiseSize", guiParameters.ssaoNoiseSize);
        ssaoShader.setFloat("radius", guiParameters.ssaoRadius);
        ssaoShader.setFloat("bias", guiParameters.ssaoBias);

        for (unsigned int i = 0; i < guiParameters.ssaoKernelSize; ++i)
        {
            ssaoShader.setVec3("samples[" + std::to_string(i) + "]", ssaoUtils.GetSamplePosition(i));
        }
    }

    // TODO move
    void UpdateSsaoFinalShader(const GuiParameters& guiParameters, Shader& ssaoFinalShader)
    {
        ssaoFinalShader.setInt("enableSsao", static_cast<int>(guiParameters.enableSsao));
    }

    // TODO move
    void UpdateSsaoNoiseTexture(const GuiParameters& guiParameters, const SsaoUtils& ssaoUtils, Texture& ssaoNoiseTexture)
    {   
        ssaoNoiseTexture = Texture(ssaoNoiseTexture.GetTextureUnitEnum(), guiParameters.ssaoNoiseSize, guiParameters.ssaoNoiseSize, GL_RGBA32F, GL_RGB, GL_FLOAT, GL_NEAREST, GL_REPEAT, ssaoUtils.GetNoise());
    }

    // TODO move
    glm::mat4 GetLightSpaceMatrix(const GuiParameters& guiParameters)
    {
        const float size = 40.0f;
        const glm::vec3 lightPosition = -guiParameters.directionalLight.direction * 2.0f;
        const glm::mat4 lightProjection = glm::ortho(-size, size, -size, size, -size, size);
        const glm::mat4 lightView = glm::lookAt(lightPosition, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
        const glm::mat4 lightSpace = lightProjection * lightView;
        return lightSpace;
    }

    // TODO move
    void DrawTransparentCube()
    {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glCullFace(GL_BACK);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glDisable(GL_CULL_FACE);
    }
}

int main()
{
    auto window = InitGlfw();
    InitGlad();
    InitGl();
    
    DisplayProperties displayProperties = Factory::MakeDisplayProperties();
    GuiParameters guiParameters = Factory::MakeGuiParameters();
    GuiUpdateFlags guiUpdateFlags;
        
    Shader ssaoInputShader(FileSystem::getPath("src/shaders/SsaoInput.vert").c_str(), FileSystem::getPath("src/shaders/SsaoInput.frag").c_str());
    Shader ssaoShader(FileSystem::getPath("src/shaders/Ssao.vert").c_str(), FileSystem::getPath("src/shaders/Ssao.frag").c_str());
    Shader ssaoBlurShader(FileSystem::getPath("src/shaders/Ssao.vert").c_str(), FileSystem::getPath("src/shaders/SsaoBlur.frag").c_str());
    Shader ssaoFinalShader(FileSystem::getPath("src/shaders/SsaoFinal.vert").c_str(), FileSystem::getPath("src/shaders/SsaoFinal.frag").c_str());
    Shader lightSourceShader(FileSystem::getPath("src/shaders/LightSource.vert").c_str(), FileSystem::getPath("src/shaders/LightSource.frag").c_str());
    Shader shadowMapShader(FileSystem::getPath("src/shaders/ShadowMap.vert").c_str(), FileSystem::getPath("src/shaders/ShadowMap.frag").c_str());
    Shader shadowMapDebugQuadShader(FileSystem::getPath("src/shaders/DebugQuad.vert").c_str(), FileSystem::getPath("src/shaders/DebugQuadDepth.frag").c_str());
    Shader ssaoDebugQuadShader(FileSystem::getPath("src/shaders/DebugQuad.vert").c_str(), FileSystem::getPath("src/shaders/DebugQuadColor.frag").c_str());

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
    Texture shadowMapTexture(GL_TEXTURE10, Config::shadowMapWidth, Config::shadowMapHeight, GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, GL_FLOAT, GL_NEAREST, GL_CLAMP_TO_BORDER);    
    
    shadowMapTexture.AddBorder();

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

    FrameBuffer shadowFrameBuffer;
    shadowFrameBuffer.Bind();
    shadowFrameBuffer.AttachTexture(GL_DEPTH_ATTACHMENT, shadowMapTexture);
    shadowFrameBuffer.Check();
    shadowFrameBuffer.Unbind();

    ssaoShader.use();
    ssaoShader.setVec2("windowSize", glm::vec2(Config::windowWidth, Config::windowHeight));
    ssaoShader.setInt("gPosition", ssaoPositionTexture.GetTextureUnit());
    ssaoShader.setInt("gNormal", ssaoNormalTexture.GetTextureUnit());
    ssaoShader.setInt("texNoise", ssaoNoiseTexture.GetTextureUnit());
    UpdateSsaoShader(guiParameters, ssaoUtils, ssaoShader);

    ssaoBlurShader.use();
    ssaoBlurShader.setInt("ssaoInput", ssaoTexture.GetTextureUnit());

    ssaoFinalShader.use();
    ssaoFinalShader.setInt("ssaoPosition", ssaoPositionTexture.GetTextureUnit());
    ssaoFinalShader.setInt("ssaoLightSpacePosition", ssaoLightSpacePositionTexture.GetTextureUnit());
    ssaoFinalShader.setInt("ssaoNormal", ssaoNormalTexture.GetTextureUnit());
    ssaoFinalShader.setInt("ssaoAlbedo", ssaoAlbedoTexture.GetTextureUnit());
    ssaoFinalShader.setInt("ssaoPointLightsContribution", ssaoPointLightsContributionTexture.GetTextureUnit());
    ssaoFinalShader.setInt("ssaoMap", ssaoTexture.GetTextureUnit());
    ssaoFinalShader.setInt("shadowMap", shadowMapTexture.GetTextureUnit());
    ssaoFinalShader.setInt("enableSsao", guiParameters.enableSsao);

    shadowMapDebugQuadShader.use();
    shadowMapDebugQuadShader.setInt("shadowMap", shadowMapTexture.GetTextureUnit());

    Camera camera(-2.25293994f, 9.60278416f, -4.95751047f, 0.00000000f, 1.00000000f, 0.00000000f, 389.10012817f, -30.39993668f);
    UnitPlane plane;
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
            UpdateSsaoShader(guiParameters, ssaoUtils, ssaoShader);
            ssaoFinalShader.use();
            UpdateSsaoFinalShader(guiParameters, ssaoFinalShader);
            guiUpdateFlags.ssaoParametersChanged = false;
        }

        const glm::mat4 lightSpaceMatrix = GetLightSpaceMatrix(guiParameters);

        // ------------------------------------------------  Create shadow map
        shadowFrameBuffer.Bind();

        glViewport(0, 0, Config::shadowMapWidth, Config::shadowMapHeight);
        glClear(GL_DEPTH_BUFFER_BIT);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);

        shadowMapShader.use();
        shadowMapShader.setMat4("lightSpace", lightSpaceMatrix);
        
        shadowFrameBuffer.Unbind();
        glDisable(GL_CULL_FACE);

        glViewport(0, 0, inputHandler.GetWindowWidth(), inputHandler.GetWindowHeight());
        glDisable(GL_BLEND);

                
        // ------------------------------------------------  SSAO pass 1 (input)
        ssaoInputFrameBuffer.Bind(); 
        ssaoInputShader.use();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        UpdateMatricesInShader(camera, ssaoInputShader);
        ssaoInputShader.setMat4("lightSpace", lightSpaceMatrix);

        ssaoInputFrameBuffer.Unbind();


        // ------------------------------------------------  SSAO pass 2 (ssao)
        ssaoFrameBuffer.Bind();
        ssaoShader.use();
        UpdateMatricesInShader(camera, ssaoShader);
        glClear(GL_COLOR_BUFFER_BIT);
        ssaoPositionTexture.Bind();
        ssaoNormalTexture.Bind();
        ssaoNoiseTexture.Bind();
        RenderQuad();
        ssaoFrameBuffer.Unbind();


        // ------------------------------------------------  SSAO pass 3 (blur)
        ssaoBlurFrameBuffer.Bind();
        ssaoBlurShader.use();
        glClear(GL_COLOR_BUFFER_BIT);
        ssaoTexture.Bind();
        RenderQuad();
        ssaoBlurFrameBuffer.Unbind();

          
        // ------------------------------------------------  SSAO pass 4 (compositing)        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDepthMask(GL_FALSE);
        ssaoFinalShader.use();
        UpdateLightingParametersInShader(guiParameters, ssaoFinalShader);
        ssaoPositionTexture.Bind();
        ssaoLightSpacePositionTexture.Bind();
        ssaoNormalTexture.Bind();
        ssaoAlbedoTexture.Bind();
        ssaoPointLightsContributionTexture.Bind();
        ssaoBlurTexture.Bind();
        shadowMapTexture.Bind();
        RenderQuad();
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
            UpdateMatricesInShader(camera, lightSourceShader);

            for (unsigned int i = 0; i < Config::numPointLights; ++i)
            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), guiParameters.pointLights[i].position) * Constants::lightSourceCubeScalingMatrix;
                lightSourceShader.setMat4("model", model);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
        }

        // ------------------------------------------------  Debug rendering of shadow map
        if (displayProperties.showShadowMap)
        {
            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            shadowMapDebugQuadShader.use();
            shadowMapTexture.Bind();
            RenderQuad();
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
            RenderQuad();
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
