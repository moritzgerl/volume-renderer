#include <renderpass/MakeRenderPasses.h>
#include <renderpass/RenderPassId.h>
#include <buffers/FrameBufferId.h>
#include <camera/Camera.h>
#include <config/Config.h>
#include <input/DisplayProperties.h>
#include <gui/GuiParameters.h>
#include <primitives/ScreenQuad.h>
#include <shader/ShaderId.h>
#include <shader/UpdateCameraMatricesInShader.h>
#include <shader/UpdateLightingParametersInShader.h>
#include <shader/UpdateLightSourceModelMatrixInShader.h>
#include <storage/TextureStorage.h>
#include <storage/ShaderStorage.h>
#include <storage/FrameBufferStorage.h>
#include <textures/TextureId.h>
#include <utils/SsaoUtils.h>

#include <glad/glad.h>

std::vector<RenderPass> Factory::MakeRenderPasses(
    const Camera& camera,
    const DisplayProperties& displayProperties,
    const GuiParameters& guiParameters,
    const SsaoUtils& ssaoUtils,
    const glm::mat4& lightSpaceMatrix,
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

        const auto& shader = shaderStorage.GetShader(ShaderId::SsaoInput);

        auto prepareFunction = [&camera, &lightSpaceMatrix, &shader]()
        {
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            ShaderUtils::UpdateCameraMatricesInShader(camera, shader);
            shader.SetMat4("lightSpace", lightSpaceMatrix);
        };

        auto renderFunction = []()
        {
            // TODO render something
        };

        renderPasses.emplace_back(
            RenderPassId::SsaoInput,
            screenQuad,
            shader,
            frameBufferStorage.GetFrameBuffer(FrameBufferId::SsaoInput),
            std::move(textures),
            std::move(prepareFunction),
            std::move(renderFunction)
        );
    }

    // SSAO
    {
        std::vector<std::reference_wrapper<const Texture>> textures;
        // TODO use { }
        textures.push_back(std::cref(textureStorage.GetTexture(TextureId::SsaoPosition)));
        textures.push_back(std::cref(textureStorage.GetTexture(TextureId::SsaoNormal)));
        textures.push_back(std::cref(textureStorage.GetTexture(TextureId::SsaoNoise)));

        const auto& shader = shaderStorage.GetShader(ShaderId::Ssao);

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
            frameBufferStorage.GetFrameBuffer(FrameBufferId::Ssao),
            std::move(textures),
            std::move(prepareFunction),
            std::move(renderFunction)
        );
    }

    // SSAO Blur
    {
        std::vector<std::reference_wrapper<const Texture>> textures;
        // TODO use { }
        textures.push_back(std::cref(textureStorage.GetTexture(TextureId::Ssao)));

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
            shaderStorage.GetShader(ShaderId::SsaoBlur),
            frameBufferStorage.GetFrameBuffer(FrameBufferId::SsaoBlur),
            std::move(textures),
            std::move(prepareFunction),
            std::move(renderFunction)
        );
    }

    // SSAO Final
    {
        std::vector<std::reference_wrapper<const Texture>> textures;
        // TODO use { }
        textures.push_back(std::cref(textureStorage.GetTexture(TextureId::SsaoPosition)));
        textures.push_back(std::cref(textureStorage.GetTexture(TextureId::SsaoLightSpacePosition)));
        textures.push_back(std::cref(textureStorage.GetTexture(TextureId::SsaoNormal)));
        textures.push_back(std::cref(textureStorage.GetTexture(TextureId::SsaoAlbedo)));
        textures.push_back(std::cref(textureStorage.GetTexture(TextureId::SsaoPointLightsContribution)));
        textures.push_back(std::cref(textureStorage.GetTexture(TextureId::SsaoBlur)));

        const auto& shader = shaderStorage.GetShader(ShaderId::SsaoFinal);

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
            frameBufferStorage.GetFrameBuffer(FrameBufferId::Default),
            std::move(textures),
            std::move(prepareFunction),
            std::move(renderFunction)
        );
    }

    // Light Source
    {
        std::vector<std::reference_wrapper<const Texture>> textures;

        const auto& shader = shaderStorage.GetShader(ShaderId::LightSource);

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
                    ShaderUtils::UpdateLightSourceModelMatrixInShader(guiParameters.pointLights[i].position, shaderStorage.GetShader(ShaderId::LightSource));
                    glDrawArrays(GL_TRIANGLES, 0, 36);
                }
            }
        };

        renderPasses.emplace_back(
            RenderPassId::LightSource,
            screenQuad,
            shader,
            frameBufferStorage.GetFrameBuffer(FrameBufferId::Default),
            std::move(textures),
            std::move(prepareFunction),
            std::move(renderFunction)
        );
    }

    // Debug
    {
        std::vector<std::reference_wrapper<const Texture>> textures;
        // TODO use { }
        textures.push_back(std::cref(textureStorage.GetTexture(TextureId::SsaoBlur)));

        const auto& shader = shaderStorage.GetShader(ShaderId::DebugQuad);

        auto prepareFunction = [&textureStorage, &shader]()
        {
            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            shader.SetInt("colorTexture", textureStorage.GetTexture(TextureId::SsaoBlur).GetTextureUnit());
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
            frameBufferStorage.GetFrameBuffer(FrameBufferId::Default),
            std::move(textures),
            std::move(prepareFunction),
            std::move(renderFunction)
        );
    }

    return renderPasses;
}

