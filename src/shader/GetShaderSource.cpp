#include <shader/GetShaderSource.h>

#include <algorithm>
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

    struct ShaderFileMapping
    {
        ShaderId shaderId;
        std::string_view fileName;
    };

    constexpr std::array<ShaderFileMapping, 7> vertexShaderFileNames =
    {{
        {ShaderId::Volume, "Volume.vert"},
        {ShaderId::SsaoInput, "SsaoInput.vert"},
        {ShaderId::Ssao, "Ssao.vert"},
        {ShaderId::SsaoBlur, "Ssao.vert"},
        {ShaderId::SsaoFinal, "SsaoFinal.vert"},
        {ShaderId::DebugQuad, "DebugQuad.vert"},
        {ShaderId::LightSource, "LightSource.vert"}
    }};

    constexpr std::array<ShaderFileMapping, 7> fragmentShaderFileNames =
    {{
        {ShaderId::Volume, "Volume.frag"},
        {ShaderId::SsaoInput, "SsaoInput.frag"},
        {ShaderId::Ssao, "Ssao.frag"},
        {ShaderId::SsaoBlur, "SsaoBlur.frag"},
        {ShaderId::SsaoFinal, "SsaoFinal.frag"},
        {ShaderId::DebugQuad, "DebugQuadColor.frag"},
        {ShaderId::LightSource, "LightSource.frag"}
    }};

    std::string_view GetShaderFileName(ShaderId shaderId, ShaderType shaderType)
    {
        const auto& shaderFileNames = (shaderType == ShaderType::Vertex) ? vertexShaderFileNames : fragmentShaderFileNames;

        const auto it = std::find_if(shaderFileNames.begin(), shaderFileNames.end(),
            [shaderId](const ShaderFileMapping& mapping)
            {
                return mapping.shaderId == shaderId;
            });

        if (it == shaderFileNames.end())
        {
            throw std::runtime_error{"Unknown shader ID"};
        }

        return it->fileName;
    }

    std::array<std::string, 7>& GetVertexShaderCache()
    {
        static auto cache = std::array<std::string, 7>{};
        return cache;
    }

    std::array<std::string, 7>& GetFragmentShaderCache()
    {
        static auto cache = std::array<std::string, 7>{};
        return cache;
    }
}

namespace ShaderSource
{
    std::string_view GetShaderSource(ShaderId shaderId, ShaderType shaderType)
    {
        auto& cache = (shaderType == ShaderType::Vertex) ? GetVertexShaderCache() : GetFragmentShaderCache();
        const auto shaderIndex = static_cast<size_t>(shaderId);

        if (cache[shaderIndex].empty())
        {
            const auto shaderDir = GetShaderDirectory();
            const auto fileName = GetShaderFileName(shaderId, shaderType);
            const auto filePath = shaderDir / fileName;

            cache[shaderIndex] = LoadShaderFile(filePath);
        }

        return cache[shaderIndex];
    }
}
