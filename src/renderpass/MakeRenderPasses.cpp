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
        const Gui& gui,
        const GuiParameters& guiParameters,
        const InputHandler& inputHandler,
        const TextureStorage& textureStorage,
        const ShaderStorage& shaderStorage,
        const FrameBufferStorage& frameBufferStorage,
        const UnitCube& unitCube
        )
    {
        auto textures = std::vector<std::reference_wrapper<const Texture>>{};
        textures.push_back(std::cref(textureStorage.GetElement(TextureId::VolumeData)));
        textures.push_back(std::cref(textureStorage.GetElement(TextureId::TransferFunction)));

        const auto& shader = shaderStorage.GetElement(ShaderId::Volume);

        auto prepareFunction = [&camera, &gui, &guiParameters, &inputHandler, &shader]()
        {
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            const auto viewportWidth = static_cast<float>(inputHandler.GetWindowWidth() - static_cast<int>(gui.GetGuiWidth()));
            const auto viewportHeight = static_cast<float>(inputHandler.GetWindowHeight());
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

    RenderPasses renderPasses =
    {
        MakeSetupRenderPass(gui, inputHandler, shaderStorage, frameBufferStorage),
        MakeRaycastingRenderPass(camera, gui, guiParameters, inputHandler, textureStorage, shaderStorage, frameBufferStorage, unitCube)
    };

/*
    // SSAO Input
    // TODO - remove?
    {
        std::vector<std::reference_wrapper<const Texture>> textures;

        const auto& shader = shaderStorage.GetElement(ShaderId::SsaoInput);

        auto prepareFunction = [&camera, &shader]()
        {
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            ShaderUtils::UpdateCameraMatricesInShader(camera, shader);
        };

        auto renderFunction = [&unitCube]()
        {
            unitCube.Render();
        };

        renderPasses.emplace_back(
            RenderPassId::SsaoInput,
            shader,
            frameBufferStorage.GetElement(FrameBufferId::SsaoInput),
            std::move(textures),
            std::move(prepareFunction),
            std::move(renderFunction)
        );
    }

    // SSAO
    {
        std::vector<std::reference_wrapper<const Texture>> textures;
        // TODO use { }
        textures.push_back(std::cref(textureStorage.GetElement(TextureId::SsaoPosition)));
        textures.push_back(std::cref(textureStorage.GetElement(TextureId::SsaoNormal)));
        textures.push_back(std::cref(textureStorage.GetElement(TextureId::SsaoNoise)));

        const auto& shader = shaderStorage.GetElement(ShaderId::Ssao);

        auto prepareFunction = [&camera, &shader]()
        {
            ShaderUtils::UpdateCameraMatricesInShader(camera, shader);
            glClear(GL_COLOR_BUFFER_BIT);
        };

        auto renderFunction = [&screenQuad]()
        {
            screenQuad.Render();
        };

        renderPasses.emplace_back(
            RenderPassId::Ssao,
            shader,
            frameBufferStorage.GetElement(FrameBufferId::Ssao),
            std::move(textures),
            std::move(prepareFunction),
            std::move(renderFunction)
        );
    }

    // SSAO Blur
    {
        std::vector<std::reference_wrapper<const Texture>> textures;
        // TODO use { }
        textures.push_back(std::cref(textureStorage.GetElement(TextureId::Ssao)));

        auto prepareFunction = []()
        {
            glClear(GL_COLOR_BUFFER_BIT);
        };

        auto renderFunction = [&screenQuad]()
        {
            screenQuad.Render();
        };

        renderPasses.emplace_back(
            RenderPassId::SsaoBlur,
            shaderStorage.GetElement(ShaderId::SsaoBlur),
            frameBufferStorage.GetElement(FrameBufferId::SsaoBlur),
            std::move(textures),
            std::move(prepareFunction),
            std::move(renderFunction)
        );
    }

    // SSAO Final
    {
        std::vector<std::reference_wrapper<const Texture>> textures;
        // TODO use { }
        textures.push_back(std::cref(textureStorage.GetElement(TextureId::SsaoPosition)));
        textures.push_back(std::cref(textureStorage.GetElement(TextureId::SsaoNormal)));
        textures.push_back(std::cref(textureStorage.GetElement(TextureId::SsaoAlbedo)));
        textures.push_back(std::cref(textureStorage.GetElement(TextureId::SsaoPointLightsContribution)));
        textures.push_back(std::cref(textureStorage.GetElement(TextureId::SsaoBlur)));

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

        renderPasses.emplace_back(
            RenderPassId::SsaoFinal,
            shader,
            frameBufferStorage.GetElement(FrameBufferId::Default),
            std::move(textures),
            std::move(prepareFunction),
            std::move(renderFunction)
        );
    }

    // Light Source
    {
        std::vector<std::reference_wrapper<const Texture>> textures;

        const auto& shader = shaderStorage.GetElement(ShaderId::LightSource);

        auto prepareFunction = [&camera, &shader]()
        {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            ShaderUtils::UpdateCameraMatricesInShader(camera, shader);
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

        renderPasses.emplace_back(
            RenderPassId::LightSource,
            shader,
            frameBufferStorage.GetElement(FrameBufferId::Default),
            std::move(textures),
            std::move(prepareFunction),
            std::move(renderFunction)
        );
    }

    // Debug
    {
        std::vector<std::reference_wrapper<const Texture>> textures;
        // TODO use { }
        textures.push_back(std::cref(textureStorage.GetElement(TextureId::SsaoBlur)));

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

        renderPasses.emplace_back(
            RenderPassId::Debug,
            shader,
            frameBufferStorage.GetElement(FrameBufferId::Default),
            std::move(textures),
            std::move(prepareFunction),
            std::move(renderFunction)
        );
    }
*/
    return renderPasses;
}

