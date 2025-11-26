#include <shader/LoadShader.h>
#include <shader/GetShaderBaseFileName.h>
#include <shader/GetShaderFileExtension.h>
#include <shader/ShaderLoadingError.h>
#include <config/Config.h>

#include <filesystem>
#include <format>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

namespace
{
    std::expected<std::string, ShaderLoadingError> GetShaderFileName(ShaderId shaderId, ShaderType shaderType)
    {
        const auto shaderBaseFileName = ShaderSource::GetShaderBaseFileName(shaderId);
        if (!shaderBaseFileName.has_value())
        {
            return std::unexpected{shaderBaseFileName.error()};
        }

        const auto shaderFileExtension = ShaderSource::GetShaderFileExtension(shaderType);
        if (!shaderFileExtension.has_value())
        {
            return std::unexpected{shaderFileExtension.error()};
        }

        return std::format("{}{}", shaderBaseFileName.value(), shaderFileExtension.value());
    }

    std::expected<std::filesystem::path, ShaderLoadingError> GetShaderFilePath(ShaderId shaderId, ShaderType shaderType)
    {   
        const auto shaderFileName = GetShaderFileName(shaderId, shaderType);
        if (!shaderFileName.has_value())
        {
            return std::unexpected{shaderFileName.error()};
        }

        return Config::shadersPath / shaderFileName.value();
    }

    std::expected<std::string, ShaderLoadingError> LoadShaderFile(const std::filesystem::path& path)
    {
        auto file = std::ifstream{path};
        if (!file.is_open())
        {
            return std::unexpected{ShaderLoadingError::FileOpenFailed};
        }

        auto stream = std::stringstream{};
        stream << file.rdbuf();
        return stream.str();
    }
}

namespace ShaderSource
{
    std::expected<std::string, ShaderLoadingError> LoadShader(ShaderId shaderId, ShaderType shaderType)
    {
        const auto shaderFilePath = GetShaderFilePath(shaderId, shaderType);
        if (!shaderFilePath.has_value())
        {
            return std::unexpected{shaderFilePath.error()};
        }

        return LoadShaderFile(shaderFilePath.value());
    }
}
