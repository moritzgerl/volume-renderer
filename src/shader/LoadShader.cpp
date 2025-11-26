#include <shader/LoadShader.h>
#include <shader/GetShaderBaseFileName.h>
#include <shader/GetShaderFileExtension.h>
#include <shader/ShaderLoadingError.h>

#include <filesystem>
#include <format>
#include <fstream>
#include <source_location>
#include <sstream>
#include <stdexcept>
#include <string>

namespace
{
    std::filesystem::path GetShadersDirectory()
    {
        const auto currentSourceFileLocation = std::source_location::current();
        auto currentSourceFilePath = std::filesystem::path{ currentSourceFileLocation.file_name()};

        // LoadShader.cpp is in src/shader/
        // We want to go to src/shaders/
        auto shadersDirectory = currentSourceFilePath.parent_path().parent_path() / "shaders";

        return shadersDirectory;
    }

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
        const auto shadersDirectory = GetShadersDirectory();
        const auto shaderFileName = GetShaderFileName(shaderId, shaderType);
        if (!shaderFileName.has_value())
        {
            return std::unexpected{shaderFileName.error()};
        }

        return shadersDirectory / shaderFileName.value();
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
