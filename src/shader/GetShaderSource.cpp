#include <shader/GetShaderSource.h>
#include <shader/GetShaderBaseFileName.h>
#include <shader/GetShaderFileExtension.h>

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

        // GetShaderSource.cpp is in src/shader/
        // We want to go to src/shaders/
        auto shadersDirectory = currentSourceFilePath.parent_path().parent_path() / "shaders";

        return shadersDirectory;
    }

    std::string GetShaderFileName(ShaderId shaderId, ShaderType shaderType)
    {
        const auto shaderBaseFileName = ShaderSource::GetShaderBaseFileName(shaderId);
        const auto shaderFileExtension = ShaderSource::GetShaderFileExtension(shaderType);
        return std::format("{}{}", shaderBaseFileName, shaderFileExtension);
    }

    std::filesystem::path GetShaderFilePath(ShaderId shaderId, ShaderType shaderType)
    {
        const auto shadersDirectory = GetShadersDirectory();
        const auto shaderFileName = GetShaderFileName(shaderId, shaderType);
        return shadersDirectory / shaderFileName;
    }

    std::string LoadShaderFile(const std::filesystem::path& path)
    {
        auto file = std::ifstream{path};
        if (!file.is_open())
        {
            throw std::runtime_error{"Failed to open shader file: " + path.string()};
        }

        auto stream = std::stringstream{};
        stream << file.rdbuf();
        return stream.str();
    }
}

namespace ShaderSource
{
    std::string GetShaderSource(ShaderId shaderId, ShaderType shaderType)
    {
        const auto shaderFilePath = GetShaderFilePath(shaderId, shaderType);
        return LoadShaderFile(shaderFilePath);
    }
}
