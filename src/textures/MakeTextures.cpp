#include <textures/MakeTextures.h>
#include <textures/TextureId.h>
#include <config/Config.h>
#include <utils/SsaoUtils.h>
#include <glad/glad.h>

namespace Factory
{
    std::vector<Texture> MakeTextures(const SsaoUtils& ssaoUtils)
    {
        std::vector<Texture> textures;
        textures.reserve(9);

        textures.emplace_back(TextureId::VolumeData, GL_TEXTURE1, Config::windowWidth, Config::windowHeight, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, GL_NEAREST, GL_REPEAT);
        textures.emplace_back(TextureId::SsaoPosition, GL_TEXTURE2, Config::windowWidth, Config::windowHeight, GL_RGBA16F, GL_RGBA, GL_FLOAT, GL_NEAREST, GL_CLAMP_TO_EDGE);
        textures.emplace_back(TextureId::SsaoNormal, GL_TEXTURE3, Config::windowWidth, Config::windowHeight, GL_RGBA16F, GL_RGBA, GL_FLOAT, GL_NEAREST, GL_REPEAT);
        textures.emplace_back(TextureId::SsaoAlbedo, GL_TEXTURE4, Config::windowWidth, Config::windowHeight, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, GL_NEAREST, GL_REPEAT);
        textures.emplace_back(TextureId::Ssao, GL_TEXTURE5, Config::windowWidth, Config::windowHeight, GL_RED, GL_RED, GL_FLOAT, GL_NEAREST, GL_REPEAT);
        textures.emplace_back(TextureId::SsaoBlur, GL_TEXTURE6, Config::windowWidth, Config::windowHeight, GL_RED, GL_RED, GL_FLOAT, GL_NEAREST, GL_REPEAT);
        textures.emplace_back(TextureId::SsaoNoise, GL_TEXTURE7, Config::defaultSsaoNoiseSize, Config::defaultSsaoNoiseSize, GL_RGBA32F, GL_RGB, GL_FLOAT, GL_NEAREST, GL_REPEAT, ssaoUtils.GetNoise());
        textures.emplace_back(TextureId::SsaoStencil, GL_TEXTURE8, Config::windowWidth, Config::windowHeight, GL_RED, GL_RED, GL_FLOAT, GL_NEAREST, GL_REPEAT);
        textures.emplace_back(TextureId::SsaoPointLightsContribution, GL_TEXTURE9, Config::windowWidth, Config::windowHeight, GL_RED, GL_RED, GL_FLOAT, GL_NEAREST, GL_REPEAT);

        return textures;
    }
}
