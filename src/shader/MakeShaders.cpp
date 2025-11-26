#include <shader/MakeShaders.h>
#include <shader/ShaderId.h>

#include <config/Config.h>
#include <gui/GuiParameters.h>
#include <shader/GetShaderSource.h>
#include <shader/ShaderLoadingError.h>
#include <shader/ShaderType.h>
#include <ssao/SsaoKernel.h>
#include <storage/ElementStorage.h>
#include <textures/Texture.h>
#include <textures/TextureId.h>

#include <glm/glm.hpp>
#include <cstdlib>
#include <iostream>
#include <string>

namespace
{
    std::string GetErrorMessage(ShaderLoadingError error)
    {
        switch (error)
        {
            case ShaderLoadingError::UnknownShaderType:
                return "Unknown shader type";
            case ShaderLoadingError::UnknownShaderId:
                return "Unknown shader ID";
            case ShaderLoadingError::FileOpenFailed:
                return "Failed to open shader file";
            default:
                return "Unknown error";
        }
    }

    std::string GetShaderSourceOrExit(ShaderId shaderId, ShaderType shaderType)
    {
        const auto result = ShaderSource::GetShaderSource(shaderId, shaderType);
        if (!result.has_value())
        {
            std::cerr << "Shader loading failed: " << GetErrorMessage(result.error()) << std::endl;
            std::exit(EXIT_FAILURE);
        }
        return result.value();
    }

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
        shaders.emplace_back(ShaderId::Volume, GetShaderSourceOrExit(ShaderId::Volume, ShaderType::Vertex), GetShaderSourceOrExit(ShaderId::Volume, ShaderType::Fragment));
        shaders.emplace_back(ShaderId::SsaoInput, GetShaderSourceOrExit(ShaderId::SsaoInput, ShaderType::Vertex), GetShaderSourceOrExit(ShaderId::SsaoInput, ShaderType::Fragment));
        shaders.emplace_back(ShaderId::Ssao, GetShaderSourceOrExit(ShaderId::Ssao, ShaderType::Vertex), GetShaderSourceOrExit(ShaderId::Ssao, ShaderType::Fragment));
        shaders.emplace_back(ShaderId::SsaoBlur, GetShaderSourceOrExit(ShaderId::SsaoBlur, ShaderType::Vertex), GetShaderSourceOrExit(ShaderId::SsaoBlur, ShaderType::Fragment));
        shaders.emplace_back(ShaderId::SsaoFinal, GetShaderSourceOrExit(ShaderId::SsaoFinal, ShaderType::Vertex), GetShaderSourceOrExit(ShaderId::SsaoFinal, ShaderType::Fragment));
        shaders.emplace_back(ShaderId::DebugQuad, GetShaderSourceOrExit(ShaderId::DebugQuad, ShaderType::Vertex), GetShaderSourceOrExit(ShaderId::DebugQuad, ShaderType::Fragment));
        shaders.emplace_back(ShaderId::LightSource, GetShaderSourceOrExit(ShaderId::LightSource, ShaderType::Vertex), GetShaderSourceOrExit(ShaderId::LightSource, ShaderType::Fragment));

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
 