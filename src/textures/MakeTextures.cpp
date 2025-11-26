#include <textures/MakeTextures.h>
#include <textures/TextureId.h>

#include <config/Config.h>
#include <config/TransferFunctionConstants.h>
#include <ssao/SsaoKernel.h>
#include <volumedata/MakeVolumeDataTexture.h>

#include <glad/glad.h>

namespace Factory
{
    std::vector<Texture> MakeTextures(const VolumeData::VolumeData& volumeData, const SsaoKernel& ssaoKernel)
    {
        return 
        {
            { MakeVolumeDataTexture(TextureId::VolumeData, GL_TEXTURE1, volumeData) },
            { TextureId::TransferFunction, GL_TEXTURE2, static_cast<unsigned int>(TransferFunctionConstants::textureSize), GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, GL_LINEAR, GL_CLAMP_TO_EDGE, nullptr },
            { TextureId::SsaoPosition, GL_TEXTURE3, Config::windowWidth, Config::windowHeight, GL_RGBA16F, GL_RGBA, GL_FLOAT, GL_NEAREST, GL_CLAMP_TO_EDGE },
            { TextureId::SsaoNormal, GL_TEXTURE4, Config::windowWidth, Config::windowHeight, GL_RGBA16F, GL_RGBA, GL_FLOAT, GL_NEAREST, GL_REPEAT },
            { TextureId::SsaoAlbedo, GL_TEXTURE5, Config::windowWidth, Config::windowHeight, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, GL_NEAREST, GL_REPEAT },
            { TextureId::Ssao, GL_TEXTURE6, Config::windowWidth, Config::windowHeight, GL_RED, GL_RED, GL_FLOAT, GL_NEAREST, GL_REPEAT },
            { TextureId::SsaoBlur, GL_TEXTURE7, Config::windowWidth, Config::windowHeight, GL_RED, GL_RED, GL_FLOAT, GL_NEAREST, GL_REPEAT },
            { TextureId::SsaoNoise, GL_TEXTURE8, Config::defaultSsaoNoiseSize, Config::defaultSsaoNoiseSize, GL_RGBA32F, GL_RGB, GL_FLOAT, GL_NEAREST, GL_REPEAT, ssaoKernel.GetNoise() },
            { TextureId::SsaoPointLightsContribution, GL_TEXTURE9, Config::windowWidth, Config::windowHeight, GL_RED, GL_RED, GL_FLOAT, GL_NEAREST, GL_REPEAT }
        };
    }
}
