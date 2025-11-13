#include <shader/MakeShaders.h>
#include <shader/ShaderId.h>

#include <config/Config.h>
#include <gui/GuiParameters.h>
#include <ssao/SsaoUtils.h>
#include <storage/ElementStorage.h>
#include <textures/Texture.h>
#include <textures/TextureId.h>
#include <utils/FileSystem.h>

#include <glm/glm.hpp>
#include <string>

namespace
{
    const Shader& GetShader(const std::vector<Shader>& shaders, ShaderId shaderId)
    {
        auto shaderIter = std::find_if(shaders.cbegin(), shaders.cend(),
            [shaderId](const Shader& shader)
            {
                return shader.GetId() == shaderId;
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
        shaders.reserve(7);

        // TODO use initializer list
        shaders.emplace_back(ShaderId::Volume, FileSystem::getPath("src/shaders/Volume.vert").c_str(), FileSystem::getPath("src/shaders/Volume.frag").c_str());
        shaders.emplace_back(ShaderId::SsaoInput, FileSystem::getPath("src/shaders/SsaoInput.vert").c_str(), FileSystem::getPath("src/shaders/SsaoInput.frag").c_str());
        shaders.emplace_back(ShaderId::Ssao, FileSystem::getPath("src/shaders/Ssao.vert").c_str(), FileSystem::getPath("src/shaders/Ssao.frag").c_str());
        shaders.emplace_back(ShaderId::SsaoBlur, FileSystem::getPath("src/shaders/Ssao.vert").c_str(), FileSystem::getPath("src/shaders/SsaoBlur.frag").c_str());
        shaders.emplace_back(ShaderId::SsaoFinal, FileSystem::getPath("src/shaders/SsaoFinal.vert").c_str(), FileSystem::getPath("src/shaders/SsaoFinal.frag").c_str());
        shaders.emplace_back(ShaderId::DebugQuad, FileSystem::getPath("src/shaders/DebugQuad.vert").c_str(), FileSystem::getPath("src/shaders/DebugQuadColor.frag").c_str());
        shaders.emplace_back(ShaderId::LightSource, FileSystem::getPath("src/shaders/LightSource.vert").c_str(), FileSystem::getPath("src/shaders/LightSource.frag").c_str());

        const Texture& volumeTexture = textureStorage.GetElement(TextureId::VolumeData);
        const Texture& transferFunctionTexture = textureStorage.GetElement(TextureId::TransferFunction);
        const Texture& ssaoPositionTexture = textureStorage.GetElement(TextureId::SsaoPosition);
        const Texture& ssaoNormalTexture = textureStorage.GetElement(TextureId::SsaoNormal);
        const Texture& ssaoAlbedoTexture = textureStorage.GetElement(TextureId::SsaoAlbedo);
        const Texture& ssaoTexture = textureStorage.GetElement(TextureId::Ssao);
        const Texture& ssaoNoiseTexture = textureStorage.GetElement(TextureId::SsaoNoise);
        const Texture& ssaoPointLightsContributionTexture = textureStorage.GetElement(TextureId::SsaoPointLightsContribution);

        const Shader& volumeShader = GetShader(shaders, ShaderId::Volume);
        volumeShader.Use();
        volumeShader.SetInt("volumeTexture", volumeTexture.GetTextureUnit());
        volumeShader.SetInt("transferFunctionTexture", transferFunctionTexture.GetTextureUnit());
        // TODO set view vector and camera pos every frame
        volumeShader.SetFloat("stepSize", 0.1f); // TODO add to gui parameters
        volumeShader.SetInt("maxSteps", 128); // TODO make configurable

        const Shader& ssaoShader = GetShader(shaders, ShaderId::Ssao);
        ssaoShader.Use();
        ssaoShader.SetVec2("windowSize", glm::vec2(Config::windowWidth, Config::windowHeight));
        ssaoShader.SetInt("gPosition", ssaoPositionTexture.GetTextureUnit());
        ssaoShader.SetInt("gNormal", ssaoNormalTexture.GetTextureUnit());
        ssaoShader.SetInt("texNoise", ssaoNoiseTexture.GetTextureUnit());
        ssaoShader.SetInt("kernelSize", guiParameters.ssaoKernelSize);
        ssaoShader.SetInt("noiseSize", guiParameters.ssaoNoiseSize);
        ssaoShader.SetFloat("radius", guiParameters.ssaoRadius);
        ssaoShader.SetFloat("bias", guiParameters.ssaoBias);
        for (unsigned int i = 0; i < guiParameters.ssaoKernelSize; ++i)
        {
            ssaoShader.SetVec3("samples[" + std::to_string(i) + "]", ssaoUtils.GetSamplePosition(i));
        }

        const Shader& ssaoBlurShader = GetShader(shaders, ShaderId::SsaoBlur);
        ssaoBlurShader.Use();
        ssaoBlurShader.SetInt("ssaoInput", ssaoTexture.GetTextureUnit());

        const Shader& ssaoFinalShader = GetShader(shaders, ShaderId::SsaoFinal);
        ssaoFinalShader.Use();
        ssaoFinalShader.SetInt("ssaoPosition", ssaoPositionTexture.GetTextureUnit());
        ssaoFinalShader.SetInt("ssaoNormal", ssaoNormalTexture.GetTextureUnit());
        ssaoFinalShader.SetInt("ssaoAlbedo", ssaoAlbedoTexture.GetTextureUnit());
        ssaoFinalShader.SetInt("ssaoPointLightsContribution", ssaoPointLightsContributionTexture.GetTextureUnit());
        ssaoFinalShader.SetInt("ssaoMap", ssaoTexture.GetTextureUnit());
        ssaoFinalShader.SetInt("enableSsao", guiParameters.enableSsao);

        return shaders;
    }
}
 