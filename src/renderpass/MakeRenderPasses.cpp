#include <renderpass/MakeRenderPasses.h>
#include <renderpass/RenderPassId.h>
#include <buffers/FrameBuffer.h>
#include <buffers/FrameBufferId.h>
#include <camera/Camera.h>
#include <config/Config.h>
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
#include <storage/ElementStorage.h>
#include <storage/Storage.h>
#include <textures/Texture.h>
#include <textures/TextureId.h>
#include <utils/SsaoUtils.h>

#include <glad/glad.h>

RenderPasses Factory::MakeRenderPasses(const InputHandler& inputHandler, const Storage& storage)
{
    const Camera& camera = storage.GetCamera();
    const DisplayProperties& displayProperties = storage.GetDisplayProperties();
    const GuiParameters& guiParameters = storage.GetGuiParameters();
    const SsaoUtils& ssaoUtils = storage.GetSsaoUtils();
    const ScreenQuad& screenQuad = storage.GetScreenQuad();
    const UnitCube& unitCube = storage.GetUnitCube();
    const TextureStorage& textureStorage = storage.GetTextureStorage();
    const ShaderStorage& shaderStorage = storage.GetShaderStorage();
    const FrameBufferStorage& frameBufferStorage = storage.GetFrameBufferStorage();

    RenderPasses renderPasses;
    renderPasses.reserve(2);

    // Setup
    // TODO - remove? do setup in raycasting pass directly ?
    {
        std::vector<std::reference_wrapper<const Texture>> textures;

        const auto& shader = shaderStorage.GetElement(ShaderId::SsaoInput);     // Dummy shader

        auto prepareFunction = [&inputHandler]()
        {
            glViewport(0, 0, inputHandler.GetWindowWidth(), inputHandler.GetWindowHeight());
            glDisable(GL_BLEND);
        };

        auto renderFunction = []()
        {
        };

        renderPasses.emplace_back(
            RenderPassId::Setup,
            shader,
            frameBufferStorage.GetElement(FrameBufferId::Default),
            std::move(textures),
            std::move(prepareFunction),
            std::move(renderFunction)
        );
    }

    // Raycasting
    {
        std::vector<std::reference_wrapper<const Texture>> textures;
        textures.push_back(std::cref(textureStorage.GetElement(TextureId::VolumeData)));

        const auto& shader = shaderStorage.GetElement(ShaderId::Volume);

        auto prepareFunction = [&camera, &shader]()
        {
            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            ShaderUtils::UpdateCameraMatricesInShader(camera, shader);
            shader.SetVec3("cameraPos", camera.Position);
            shader.SetMat4("model", glm::mat4(1.0f));
        };

        auto renderFunction = [&unitCube]()
        {   
            unitCube.Render();
        };

        renderPasses.emplace_back(
            RenderPassId::Volume,
            shader,
            frameBufferStorage.GetElement(FrameBufferId::Default),
            std::move(textures),
            std::move(prepareFunction),
            std::move(renderFunction)
        );
    }
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

