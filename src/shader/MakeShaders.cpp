#include <shader/MakeShaders.h>
#include <shader/ShaderId.h>

#include <config/Config.h>
#include <gui/GuiParameters.h>
#include <ssao/SsaoKernel.h>
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
        const SsaoKernel& ssaoKernel,
        const TextureStorage& textureStorage
    )
    {
        auto shaders = std::vector<Shader>{};
        shaders.reserve(7);

        // TODO use initializer list
        shaders.emplace_back(ShaderId::Volume, FileSystem::GetPath("src/shaders/Volume.vert").string().c_str(), FileSystem::GetPath("src/shaders/Volume.frag").string().c_str());
        shaders.emplace_back(ShaderId::SsaoInput, FileSystem::GetPath("src/shaders/SsaoInput.vert").string().c_str(), FileSystem::GetPath("src/shaders/SsaoInput.frag").string().c_str());
        shaders.emplace_back(ShaderId::Ssao, FileSystem::GetPath("src/shaders/Ssao.vert").string().c_str(), FileSystem::GetPath("src/shaders/Ssao.frag").string().c_str());
        shaders.emplace_back(ShaderId::SsaoBlur, FileSystem::GetPath("src/shaders/Ssao.vert").string().c_str(), FileSystem::GetPath("src/shaders/SsaoBlur.frag").string().c_str());
        shaders.emplace_back(ShaderId::SsaoFinal, FileSystem::GetPath("src/shaders/SsaoFinal.vert").string().c_str(), FileSystem::GetPath("src/shaders/SsaoFinal.frag").string().c_str());
        shaders.emplace_back(ShaderId::DebugQuad, FileSystem::GetPath("src/shaders/DebugQuad.vert").string().c_str(), FileSystem::GetPath("src/shaders/DebugQuadColor.frag").string().c_str());
        shaders.emplace_back(ShaderId::LightSource, FileSystem::GetPath("src/shaders/LightSource.vert").string().c_str(), FileSystem::GetPath("src/shaders/LightSource.frag").string().c_str());

        const auto& volumeTexture = textureStorage.GetElement(TextureId::VolumeData);
        const auto& transferFunctionTexture = textureStorage.GetElement(TextureId::TransferFunction);
        const auto& ssaoPositionTexture = textureStorage.GetElement(TextureId::SsaoPosition);
        const auto& ssaoNormalTexture = textureStorage.GetElement(TextureId::SsaoNormal);
        const auto& ssaoAlbedoTexture = textureStorage.GetElement(TextureId::SsaoAlbedo);
        const auto& ssaoTexture = textureStorage.GetElement(TextureId::Ssao);
        const auto& ssaoNoiseTexture = textureStorage.GetElement(TextureId::SsaoNoise);
        const auto& ssaoPointLightsContributionTexture = textureStorage.GetElement(TextureId::SsaoPointLightsContribution);

        const auto& volumeShader = GetShader(shaders, ShaderId::Volume);
        volumeShader.Use();
        volumeShader.SetInt("volumeTexture", volumeTexture.GetTextureUnit());
        volumeShader.SetInt("transferFunctionTexture", transferFunctionTexture.GetTextureUnit());
        // TODO set view vector and camera pos every frame
        volumeShader.SetFloat("stepSize", 0.1f); // TODO add to gui parameters
        volumeShader.SetInt("maxSteps", 128); // TODO make configurable

        const Shader& ssaoShader = GetShader(shaders, ShaderId::Ssao);
        ssaoShader.Use();
        ssaoShader.SetVec2("windowSize", glm::vec2{Config::windowWidth, Config::windowHeight});
        ssaoShader.SetInt("gPosition", ssaoPositionTexture.GetTextureUnit());
        ssaoShader.SetInt("gNormal", ssaoNormalTexture.GetTextureUnit());
        ssaoShader.SetInt("texNoise", ssaoNoiseTexture.GetTextureUnit());
        ssaoShader.SetInt("kernelSize", guiParameters.ssaoKernelSize);
        ssaoShader.SetInt("noiseSize", guiParameters.ssaoNoiseSize);
        ssaoShader.SetFloat("radius", guiParameters.ssaoRadius);
        ssaoShader.SetFloat("bias", guiParameters.ssaoBias);
        for (unsigned int i = 0; i < guiParameters.ssaoKernelSize; ++i)
        {
            ssaoShader.SetVec3("samples[" + std::to_string(i) + "]", ssaoKernel.GetSamplePosition(i));
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
 