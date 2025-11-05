#include <renderpass/MakeRenderPasses.h>
#include <renderpass/RenderPassId.h>
#include <buffers/FrameBuffer.h>
#include <buffers/FrameBufferId.h>
#include <camera/Camera.h>
#include <config/Config.h>
#include <input/DisplayProperties.h>
#include <gui/GuiParameters.h>
#include <primitives/ScreenQuad.h>
#include <shader/Shader.h>
#include <shader/ShaderId.h>
#include <shader/UpdateCameraMatricesInShader.h>
#include <shader/UpdateLightingParametersInShader.h>
#include <shader/UpdateLightSourceModelMatrixInShader.h>
#include <storage/ElementStorage.h>
#include <textures/Texture.h>
#include <textures/TextureId.h>
#include <utils/SsaoUtils.h>

#include <glad/glad.h>

std::vector<RenderPass> Factory::MakeRenderPasses(
    const Camera& camera,
    const DisplayProperties& displayProperties,
    const GuiParameters& guiParameters,
    const SsaoUtils& ssaoUtils,
    const ScreenQuad& screenQuad,
    const TextureStorage& textureStorage,
    const ShaderStorage& shaderStorage,
    const FrameBufferStorage& frameBufferStorage
)
{
    std::vector<RenderPass> renderPasses;
    renderPasses.reserve(6);

    // SSAO Input
    {
        std::vector<std::reference_wrapper<const Texture>> textures;

        const auto& shader = shaderStorage.GetElement(ShaderId::SsaoInput);

        auto prepareFunction = [&camera, &shader]()
        {
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            ShaderUtils::UpdateCameraMatricesInShader(camera, shader);
        };

        auto renderFunction = []()
        {
            // TODO render something
        };

        renderPasses.emplace_back(
            RenderPassId::SsaoInput,
            screenQuad,
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
            screenQuad,
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
            screenQuad,
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
            screenQuad,
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
            screenQuad,
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
            screenQuad,
            shader,
            frameBufferStorage.GetElement(FrameBufferId::Default),
            std::move(textures),
            std::move(prepareFunction),
            std::move(renderFunction)
        );
    }

    return renderPasses;
}

