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
    std::filesystem::path GetShaderDirectory()
    {
        const auto location = std::source_location::current();
        auto sourceFile = std::filesystem::path{location.file_name()};

        // GetShaderSource.cpp is in src/shader/
        // We want to go to src/shaders/
        auto shaderDir = sourceFile.parent_path().parent_path() / "shaders";

        return shaderDir;
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

    std::filesystem::path GetShaderFilePath(ShaderId shaderId, ShaderType shaderType)
    {
        const auto shaderDir = GetShaderDirectory();
        const auto fileName = ShaderSource::GetShaderFileName(shaderId, shaderType);
        const auto filePath = shaderDir / fileName;
        return filePath;
    }
}

namespace ShaderSource
{
    std::string GetShaderSource(ShaderId shaderId, ShaderType shaderType)
    {
        const auto filePath = GetShaderFilePath(shaderId, shaderType);
        return LoadShaderFile(filePath);
    }
}
