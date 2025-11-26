#include <renderpass/MakeRenderPasses.h>
#include <renderpass/RenderPassId.h>

#include <buffers/FrameBuffer.h>
#include <buffers/FrameBufferId.h>
#include <camera/Camera.h>
#include <config/Config.h>
#include <gui/Gui.h>
#include <gui/GuiParameters.h>
#include <input/DisplayProperties.h>
#include <input/InputHandler.h>
#include <primitives/ScreenQuad.h>
#include <primitives/UnitCube.h>
#include <shader/Shader.h>
#include <shader/ShaderId.h>
#include <shader/UpdateCameraMatricesInShader.h>
#include <shader/UpdateLightingParametersInShader.h>
#include <shader/UpdateLightSourceModelMatrixInShader.h>
#include <ssao/SsaoKernel.h>
#include <storage/ElementStorage.h>
#include <storage/Storage.h>
#include <textures/Texture.h>
#include <textures/TextureId.h>

#include <glad/glad.h>

namespace
{
    RenderPass MakeSetupRenderPass(
        const Gui& gui,
        const InputHandler& inputHandler,
        const ShaderStorage& shaderStorage,
        const FrameBufferStorage& frameBufferStorage)
    {
        auto textures = std::vector<std::reference_wrapper<const Texture>>{};

        const auto& shader = shaderStorage.GetElement(ShaderId::SsaoInput);     // Dummy shader

        auto prepareFunction = [&gui, &inputHandler]()
        {
            const auto viewportX = static_cast<int>(gui.GetGuiWidth());
            const auto viewportWidth = inputHandler.GetWindowWidth() - viewportX;
            glViewport(viewportX, 0, viewportWidth, inputHandler.GetWindowHeight());
            glDisable(GL_BLEND);
        };

        auto renderFunction = []()
        {
        };

        return 
        {
            RenderPassId::Setup,
            shader,
            frameBufferStorage.GetElement(FrameBufferId::Default),
            std::move(textures),
            std::move(prepareFunction),
            std::move(renderFunction)
        };
    }

    RenderPass MakeRaycastingRenderPass(
        const Camera& camera,
        const GuiParameters& guiParameters,
        const TextureStorage& textureStorage,
        const ShaderStorage& shaderStorage,
        const FrameBufferStorage& frameBufferStorage,
        const UnitCube& unitCube,
        float viewportWidth,
        float viewportHeight
        )
    {
        auto textures = std::vector<std::reference_wrapper<const Texture>>
        {
            std::cref(textureStorage.GetElement(TextureId::VolumeData)),
            std::cref(textureStorage.GetElement(TextureId::TransferFunction))
        };
        
        const auto& shader = shaderStorage.GetElement(ShaderId::Volume);

        auto prepareFunction = [&camera, &guiParameters, &shader, viewportWidth, viewportHeight]()
        {
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            ShaderUtils::UpdateCameraMatricesInShader(camera, shader, viewportWidth, viewportHeight);
            shader.SetVec3("cameraPos", camera.GetPosition());
            shader.SetMat4("model", glm::mat4{ 1.0f });
            shader.SetFloat("densityMultiplier", guiParameters.raycastingDensityMultiplier);
        };

        auto renderFunction = [&unitCube]()
        {
            unitCube.Render();
        };

        return 
        {
            RenderPassId::Volume,
            shader,
            frameBufferStorage.GetElement(FrameBufferId::Default),
            std::move(textures),
            std::move(prepareFunction),
            std::move(renderFunction)
        };
    }

    RenderPass MakeSsaoInputRenderPass(
        const Camera& camera,
        const ShaderStorage& shaderStorage,
        const FrameBufferStorage& frameBufferStorage,
        const UnitCube& unitCube,
        float viewportWidth,
        float viewportHeight)
    {
        auto textures = std::vector<std::reference_wrapper<const Texture>>{};

        const auto& shader = shaderStorage.GetElement(ShaderId::SsaoInput);

        auto prepareFunction = [&camera, &shader, viewportWidth, viewportHeight]()
        {
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            ShaderUtils::UpdateCameraMatricesInShader(camera, shader, viewportWidth, viewportHeight);
        };

        auto renderFunction = [&unitCube]()
        {
            unitCube.Render();
        };

        return
        {
            RenderPassId::SsaoInput,
            shader,
            frameBufferStorage.GetElement(FrameBufferId::SsaoInput),
            std::move(textures),
            std::move(prepareFunction),
            std::move(renderFunction)
        };
    }

    RenderPass MakeSsaoRenderPass(
        const Camera& camera,
        const TextureStorage& textureStorage,
        const ShaderStorage& shaderStorage,
        const FrameBufferStorage& frameBufferStorage,
        const ScreenQuad& screenQuad,
        float viewportWidth,
        float viewportHeight)
    {
        auto textures = std::vector<std::reference_wrapper<const Texture>>
        {
            std::cref(textureStorage.GetElement(TextureId::SsaoPosition)),
            std::cref(textureStorage.GetElement(TextureId::SsaoNormal)),
            std::cref(textureStorage.GetElement(TextureId::SsaoNoise))
        };

        const auto& shader = shaderStorage.GetElement(ShaderId::Ssao);

        auto prepareFunction = [&camera, &shader, viewportWidth, viewportHeight]()
        {
            ShaderUtils::UpdateCameraMatricesInShader(camera, shader, viewportWidth, viewportHeight);
            glClear(GL_COLOR_BUFFER_BIT);
        };

        auto renderFunction = [&screenQuad]()
        {
            screenQuad.Render();
        };

        return
        {
            RenderPassId::Ssao,
            shader,
            frameBufferStorage.GetElement(FrameBufferId::Ssao),
            std::move(textures),
            std::move(prepareFunction),
            std::move(renderFunction)
        };
    }

    RenderPass MakeSsaoBlurRenderPass(
        const TextureStorage& textureStorage,
        const ShaderStorage& shaderStorage,
        const FrameBufferStorage& frameBufferStorage,
        const ScreenQuad& screenQuad)
    {
        auto textures = std::vector<std::reference_wrapper<const Texture>>
        {
            std::cref(textureStorage.GetElement(TextureId::Ssao))
        };

        auto prepareFunction = []()
        {
            glClear(GL_COLOR_BUFFER_BIT);
        };

        auto renderFunction = [&screenQuad]()
        {
            screenQuad.Render();
        };

        return
        {
            RenderPassId::SsaoBlur,
            shaderStorage.GetElement(ShaderId::SsaoBlur),
            frameBufferStorage.GetElement(FrameBufferId::SsaoBlur),
            std::move(textures),
            std::move(prepareFunction),
            std::move(renderFunction)
        };
    }

    RenderPass MakeSsaoFinalRenderPass(
        const GuiParameters& guiParameters,
        const TextureStorage& textureStorage,
        const ShaderStorage& shaderStorage,
        const FrameBufferStorage& frameBufferStorage,
        const ScreenQuad& screenQuad)
    {
        auto textures = std::vector<std::reference_wrapper<const Texture>>
        {
            std::cref(textureStorage.GetElement(TextureId::SsaoPosition)),
            std::cref(textureStorage.GetElement(TextureId::SsaoNormal)),
            std::cref(textureStorage.GetElement(TextureId::SsaoAlbedo)),
            std::cref(textureStorage.GetElement(TextureId::SsaoPointLightsContribution)),
            std::cref(textureStorage.GetElement(TextureId::SsaoBlur))
        };

        const auto& shader = shaderStorage.GetElement(ShaderId::SsaoFinal);

        auto prepareFunction = [&guiParameters, &shader]()
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glDepthMask(GL_FALSE);
            ShaderUtils::UpdateLightingParametersInShader(guiParameters, shader);
        };

        auto renderFunction = [&screenQuad]()
        {
            screenQuad.Render();
            glDepthMask(GL_TRUE);
        };

        return
        {
            RenderPassId::SsaoFinal,
            shader,
            frameBufferStorage.GetElement(FrameBufferId::Default),
            std::move(textures),
            std::move(prepareFunction),
            std::move(renderFunction)
        };
    }

    RenderPass MakeLightSourceRenderPass(
        const Camera& camera,
        const GuiParameters& guiParameters,
        const ShaderStorage& shaderStorage,
        const FrameBufferStorage& frameBufferStorage,
        float viewportWidth,
        float viewportHeight)
    {
        auto textures = std::vector<std::reference_wrapper<const Texture>>{};

        const auto& shader = shaderStorage.GetElement(ShaderId::LightSource);

        auto prepareFunction = [&camera, &shader, viewportWidth, viewportHeight]()
        {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            ShaderUtils::UpdateCameraMatricesInShader(camera, shader, viewportWidth, viewportHeight);
        };

        auto renderFunction = [&guiParameters, &shaderStorage]()
        {
            if (guiParameters.showLightSources)
            {
                for (unsigned int i = 0; i < Config::numPointLights; ++i)
                {
                    ShaderUtils::UpdateLightSourceModelMatrixInShader(guiParameters.pointLights[i].position, shaderStorage.GetElement(ShaderId::LightSource));
                    glDrawArrays(GL_TRIANGLES, 0, 36);
                }
            }
        };

        return
        {
            RenderPassId::LightSource,
            shader,
            frameBufferStorage.GetElement(FrameBufferId::Default),
            std::move(textures),
            std::move(prepareFunction),
            std::move(renderFunction)
        };
    }

    RenderPass MakeDebugRenderPass(
        const DisplayProperties& displayProperties,
        const TextureStorage& textureStorage,
        const ShaderStorage& shaderStorage,
        const FrameBufferStorage& frameBufferStorage,
        const ScreenQuad& screenQuad)
    {
        auto textures = std::vector<std::reference_wrapper<const Texture>>        
        {
            std::cref(textureStorage.GetElement(TextureId::SsaoBlur))
        };        

        const auto& shader = shaderStorage.GetElement(ShaderId::DebugQuad);

        auto prepareFunction = [&textureStorage, &shader]()
        {
            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            shader.SetInt("colorTexture", textureStorage.GetElement(TextureId::SsaoBlur).GetTextureUnit());
            shader.SetInt("isSingleChannel", 1);
        };

        auto renderFunction = [&displayProperties, &screenQuad]()
        {
            if (displayProperties.showSsaoMap)
            {
                screenQuad.Render();
            }
        };

        return
        {
            RenderPassId::Debug,
            shader,
            frameBufferStorage.GetElement(FrameBufferId::Default),
            std::move(textures),
            std::move(prepareFunction),
            std::move(renderFunction)
        };
    }
}


RenderPasses Factory::MakeRenderPasses(const Gui& gui, const InputHandler& inputHandler, const Storage& storage)
{
    const auto& camera = storage.GetCamera();
    const auto& displayProperties = storage.GetDisplayProperties();
    const auto& guiParameters = storage.GetGuiParameters();
    const auto& ssaoKernel = storage.GetSsaoKernel();
    const auto& screenQuad = storage.GetScreenQuad();
    const auto& unitCube = storage.GetUnitCube();
    const auto& textureStorage = storage.GetTextureStorage();
    const auto& shaderStorage = storage.GetShaderStorage();
    const auto& frameBufferStorage = storage.GetFrameBufferStorage();

    const auto viewportWidth = static_cast<float>(inputHandler.GetWindowWidth() - static_cast<int>(gui.GetGuiWidth()));
    const auto viewportHeight = static_cast<float>(inputHandler.GetWindowHeight());

    return
    {
        MakeSetupRenderPass(gui, inputHandler, shaderStorage, frameBufferStorage),
        MakeRaycastingRenderPass(camera, guiParameters, textureStorage, shaderStorage, frameBufferStorage, unitCube, viewportWidth, viewportHeight),
        // SSAO, light source, and debug passes are currently disabled
        // MakeSsaoInputRenderPass(camera, shaderStorage, frameBufferStorage, unitCube, viewportWidth, viewportHeight),
        // MakeSsaoRenderPass(camera, textureStorage, shaderStorage, frameBufferStorage, screenQuad, viewportWidth, viewportHeight),
        // MakeSsaoBlurRenderPass(textureStorage, shaderStorage, frameBufferStorage, screenQuad),
        // MakeSsaoFinalRenderPass(guiParameters, textureStorage, shaderStorage, frameBufferStorage, screenQuad),
        // MakeLightSourceRenderPass(camera, guiParameters, shaderStorage, frameBufferStorage, viewportWidth, viewportHeight),
        // MakeDebugRenderPass(displayProperties, textureStorage, shaderStorage, frameBufferStorage, screenQuad)
    };
}
