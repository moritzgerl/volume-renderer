#include <shader/GetShaderSource.h>
#include <shader/GetShaderFileName.h>

#include <array>
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

    auto vertexShaderCache = std::array<std::string, 7>{};
    auto fragmentShaderCache = std::array<std::string, 7>{};
}

namespace ShaderSource
{
    std::string_view GetShaderSource(ShaderId shaderId, ShaderType shaderType)
    {
        auto& cache = (shaderType == ShaderType::Vertex) ? vertexShaderCache : fragmentShaderCache;
        const auto shaderIndex = static_cast<size_t>(shaderId);

        if (cache[shaderIndex].empty())
        {
            const auto shaderDir = GetShaderDirectory();
            const auto fileName = ShaderSource::GetShaderFileName(shaderId, shaderType);
            const auto filePath = shaderDir / fileName;

            cache[shaderIndex] = LoadShaderFile(filePath);
        }

        return cache[shaderIndex];
    }
}
