#include <shader/MakeShaders.h>
#include <shader/ShaderId.h>
#include <shader/UpdateSsaoShader.h>
#include <storage/TextureStorage.h>
#include <textures/TextureId.h>
#include <config/Config.h>
#include <gui/GuiParameters.h>
#include <utils/SsaoUtils.h>
#include <utils/FileSystem.h>

#include <glm/glm.hpp>

namespace
{
    const Shader& GetShader(const std::vector<Shader>& shaders, ShaderId shaderId)
    {
        auto shaderIter = std::find_if(shaders.cbegin(), shaders.cend(),
            [shaderId](const Shader& shader)
            {
                return shader.GetShaderId() == shaderId;
            }
        );
        return *shaderIter;
    }
}

namespace Factory
{
    std::vector<Shader> MakeShaders(
        const GuiParameters& guiParameters,
        const SsaoUtils& ssaoUtils,
        const TextureStorage& textureStorage
    )
    {
        std::vector<Shader> shaders;
        shaders.reserve(6);

        // TODO use initializer list
        shaders.emplace_back(ShaderId::SsaoInput, FileSystem::getPath("src/shaders/SsaoInput.vert").c_str(), FileSystem::getPath("src/shaders/SsaoInput.frag").c_str());
        shaders.emplace_back(ShaderId::Ssao, FileSystem::getPath("src/shaders/Ssao.vert").c_str(), FileSystem::getPath("src/shaders/Ssao.frag").c_str());
        shaders.emplace_back(ShaderId::SsaoBlur, FileSystem::getPath("src/shaders/Ssao.vert").c_str(), FileSystem::getPath("src/shaders/SsaoBlur.frag").c_str());
        shaders.emplace_back(ShaderId::SsaoFinal, FileSystem::getPath("src/shaders/SsaoFinal.vert").c_str(), FileSystem::getPath("src/shaders/SsaoFinal.frag").c_str());
        shaders.emplace_back(ShaderId::DebugQuad, FileSystem::getPath("src/shaders/DebugQuad.vert").c_str(), FileSystem::getPath("src/shaders/DebugQuadColor.frag").c_str());
        shaders.emplace_back(ShaderId::LightSource, FileSystem::getPath("src/shaders/LightSource.vert").c_str(), FileSystem::getPath("src/shaders/LightSource.frag").c_str());

        const Texture& ssaoPositionTexture = textureStorage.GetTexture(TextureId::SsaoPosition);
        const Texture& ssaoLightSpacePositionTexture = textureStorage.GetTexture(TextureId::SsaoLightSpacePosition);
        const Texture& ssaoNormalTexture = textureStorage.GetTexture(TextureId::SsaoNormal);
        const Texture& ssaoAlbedoTexture = textureStorage.GetTexture(TextureId::SsaoAlbedo);
        const Texture& ssaoTexture = textureStorage.GetTexture(TextureId::Ssao);
        const Texture& ssaoNoiseTexture = textureStorage.GetTexture(TextureId::SsaoNoise);
        const Texture& ssaoPointLightsContributionTexture = textureStorage.GetTexture(TextureId::SsaoPointLightsContribution);

        const Shader& ssaoShader = GetShader(shaders, ShaderId::Ssao);
        ssaoShader.Use();
        ssaoShader.SetVec2("windowSize", glm::vec2(Config::windowWidth, Config::windowHeight));
        ssaoShader.SetInt("gPosition", ssaoPositionTexture.GetTextureUnit());
        ssaoShader.SetInt("gNormal", ssaoNormalTexture.GetTextureUnit());
        ssaoShader.SetInt("texNoise", ssaoNoiseTexture.GetTextureUnit());
        ShaderUtils::UpdateSsaoShader(guiParameters, ssaoUtils, ssaoShader);

        const Shader& ssaoBlurShader = GetShader(shaders, ShaderId::SsaoBlur);
        ssaoBlurShader.Use();
        ssaoBlurShader.SetInt("ssaoInput", ssaoTexture.GetTextureUnit());

        const Shader& ssaoFinalShader = GetShader(shaders, ShaderId::SsaoFinal);
        ssaoFinalShader.Use();
        ssaoFinalShader.SetInt("ssaoPosition", ssaoPositionTexture.GetTextureUnit());
        ssaoFinalShader.SetInt("ssaoLightSpacePosition", ssaoLightSpacePositionTexture.GetTextureUnit());
        ssaoFinalShader.SetInt("ssaoNormal", ssaoNormalTexture.GetTextureUnit());
        ssaoFinalShader.SetInt("ssaoAlbedo", ssaoAlbedoTexture.GetTextureUnit());
        ssaoFinalShader.SetInt("ssaoPointLightsContribution", ssaoPointLightsContributionTexture.GetTextureUnit());
        ssaoFinalShader.SetInt("ssaoMap", ssaoTexture.GetTextureUnit());
        ssaoFinalShader.SetInt("enableSsao", guiParameters.enableSsao);

        return shaders;
    }
}
 