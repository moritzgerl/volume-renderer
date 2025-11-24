#include <shader/GetShaderSource.h>

#include <filesystem>
#include <fstream>
#include <source_location>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>

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

    struct ShaderKey
    {
        ShaderId shaderId;
        bool isVertex;

        bool operator==(const ShaderKey& other) const
        {
            return shaderId == other.shaderId && isVertex == other.isVertex;
        }
    };

    struct ShaderKeyHash
    {
        std::size_t operator()(const ShaderKey& key) const
        {
            return std::hash<int>{}(static_cast<int>(key.shaderId)) ^ (std::hash<bool>{}(key.isVertex) << 1);
        }
    };

    std::unordered_map<ShaderKey, std::string, ShaderKeyHash>& GetShaderCache()
    {
        static auto cache = std::unordered_map<ShaderKey, std::string, ShaderKeyHash>{};
        return cache;
    }

    const char* GetShaderFileName(ShaderId shaderId, bool isVertex)
    {
        switch (shaderId)
        {
            case ShaderId::Volume:
                return isVertex ? "Volume.vert" : "Volume.frag";
            case ShaderId::SsaoInput:
                return isVertex ? "SsaoInput.vert" : "SsaoInput.frag";
            case ShaderId::Ssao:
                return isVertex ? "Ssao.vert" : "Ssao.frag";
            case ShaderId::SsaoBlur:
                return isVertex ? "Ssao.vert" : "SsaoBlur.frag";
            case ShaderId::SsaoFinal:
                return isVertex ? "SsaoFinal.vert" : "SsaoFinal.frag";
            case ShaderId::DebugQuad:
                return isVertex ? "DebugQuad.vert" : "DebugQuadColor.frag";
            case ShaderId::LightSource:
                return isVertex ? "LightSource.vert" : "LightSource.frag";
            default:
                throw std::runtime_error{"Unknown shader ID"};
        }
    }
}

namespace ShaderSource
{
    std::string_view GetShaderSource(ShaderId shaderId, bool isVertex)
    {
        auto& cache = GetShaderCache();
        const auto key = ShaderKey{shaderId, isVertex};

        auto it = cache.find(key);
        if (it == cache.end())
        {
            const auto shaderDir = GetShaderDirectory();
            const auto fileName = GetShaderFileName(shaderId, isVertex);
            const auto filePath = shaderDir / fileName;

            auto source = LoadShaderFile(filePath);
            it = cache.emplace(key, std::move(source)).first;
        }

        return it->second;
    }
}
