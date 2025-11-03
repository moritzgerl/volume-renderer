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
#include <storage/Storage.h>
#include <textures/TextureId.h>
#include <utils/SsaoUtils.h>

#include <glad/glad.h>

namespace Factory
{
    std::vector<RenderPass> MakeRenderPasses(
        const Storage& storage,
        const ScreenQuad& screenQuad,
        const Camera& camera,
        const DisplayProperties& displayProperties,
        const GuiParameters& guiParameters,        
        const SsaoUtils& ssaoUtils,
        const glm::mat4& lightSpaceMatrix
    )
    {
        std::vector<RenderPass> renderPasses;
        renderPasses.reserve(6);

        // SSAO Input
        {
            std::vector<std::reference_wrapper<const Texture>> textures;

            const auto& shader = storage.GetShader(ShaderId::SsaoInput);

            auto prepareFunction = [&camera, &lightSpaceMatrix, &storage, &shader]() 
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
                storage.GetFrameBuffer(FrameBufferId::SsaoInput),
                std::move(textures),
                std::move(prepareFunction),
                std::move(renderFunction)
            );
        }

        // SSAO
        {
            std::vector<std::reference_wrapper<const Texture>> textures;
            // TODO use { }
            textures.push_back(std::cref(storage.GetTexture(TextureId::SsaoPosition)));
            textures.push_back(std::cref(storage.GetTexture(TextureId::SsaoNormal)));
            textures.push_back(std::cref(storage.GetTexture(TextureId::SsaoNoise)));

            const auto& shader = storage.GetShader(ShaderId::Ssao);

            auto prepareFunction = [&camera, &storage, &shader]()
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
                shader ,
                storage.GetFrameBuffer(FrameBufferId::Ssao),
                std::move(textures),
                std::move(prepareFunction),
                std::move(renderFunction)
            );
        }

        // SSAO Blur
        {
            std::vector<std::reference_wrapper<const Texture>> textures;
            // TODO use { }
            textures.push_back(std::cref(storage.GetTexture(TextureId::Ssao)));

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
                storage.GetShader(ShaderId::SsaoBlur),
                storage.GetFrameBuffer(FrameBufferId::SsaoBlur),
                std::move(textures),
                std::move(prepareFunction),
                std::move(renderFunction)
            );
        }

        // SSAO Final
        {
            std::vector<std::reference_wrapper<const Texture>> textures;
            // TODO use { }
            textures.push_back(std::cref(storage.GetTexture(TextureId::SsaoPosition)));
            textures.push_back(std::cref(storage.GetTexture(TextureId::SsaoLightSpacePosition)));
            textures.push_back(std::cref(storage.GetTexture(TextureId::SsaoNormal)));
            textures.push_back(std::cref(storage.GetTexture(TextureId::SsaoAlbedo)));
            textures.push_back(std::cref(storage.GetTexture(TextureId::SsaoPointLightsContribution)));
            textures.push_back(std::cref(storage.GetTexture(TextureId::SsaoBlur)));

            const auto& shader = storage.GetShader(ShaderId::SsaoFinal);

            auto prepareFunction = [&guiParameters, &storage, &shader]()
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
                storage.GetFrameBuffer(FrameBufferId::Default),
                std::move(textures),
                std::move(prepareFunction),
                std::move(renderFunction)
            );
        }

        // Light Source
        {
            std::vector<std::reference_wrapper<const Texture>> textures;

            const auto& shader = storage.GetShader(ShaderId::LightSource);

            auto prepareFunction = [&camera, &storage, &shader]()
            {
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                ShaderUtils::UpdateCameraMatricesInShader(camera, shader);
            };

            auto renderFunction = [&guiParameters, &storage]()
            {
                if (guiParameters.showLightSources)
                {
                    for (unsigned int i = 0; i < Config::numPointLights; ++i)
                    {
                        ShaderUtils::UpdateLightSourceModelMatrixInShader(guiParameters.pointLights[i].position, storage.GetShader(ShaderId::LightSource));
                        glDrawArrays(GL_TRIANGLES, 0, 36);
                    }
                }
            };

            renderPasses.emplace_back(
                RenderPassId::LightSource,
                screenQuad,
                shader,
                storage.GetFrameBuffer(FrameBufferId::Default),
                std::move(textures),
                std::move(prepareFunction),
                std::move(renderFunction)
            );
        }

        // Debug
        {
            std::vector<std::reference_wrapper<const Texture>> textures;
            // TODO use { }
            textures.push_back(std::cref(storage.GetTexture(TextureId::SsaoBlur)));

            const auto& shader = storage.GetShader(ShaderId::DebugQuad);

            auto prepareFunction = [&storage, &shader]()
            {
                glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                shader.SetInt("colorTexture", storage.GetTexture(TextureId::SsaoBlur).GetTextureUnit());
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
                storage.GetFrameBuffer(FrameBufferId::Default),
                std::move(textures),
                std::move(prepareFunction),
                std::move(renderFunction)
            );
        }

        return renderPasses;
    }
}
