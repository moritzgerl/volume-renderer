#include <shader/GetShaderSource.h>
#include <shader/GetShaderFileName.h>

#include <filesystem>
#include <fstream>
#include <source_location>
#include <sstream>
#include <stdexcept>
#include <string>

namespace
{
    std::filesystem::path GetShadersDirectory()
    {
        const auto location = std::source_location::current();
        auto sourceFile = std::filesystem::path{location.file_name()};

        // GetShaderSource.cpp is in src/shader/
        // We want to go to src/shaders/
        auto shaderDir = sourceFile.parent_path().parent_path() / "shaders";

        return shaderDir;
    }

    std::filesystem::path GetShaderFilePath(ShaderId shaderId, ShaderType shaderType)
    {
        const auto shadersDirectory = GetShadersDirectory();
        const auto shaderFileName = ShaderSource::GetShaderFileName(shaderId, shaderType);
        const auto shaderFilePath = shadersDirectory / shaderFileName;
        return shaderFilePath;
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
