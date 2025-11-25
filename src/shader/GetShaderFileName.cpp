#include <shader/GetShaderFileName.h>

#include <algorithm>
#include <array>
#include <stdexcept>

namespace
{
    struct ShaderFileNameMapping
    {
        ShaderId shaderId;
        std::string_view fileName;
    };

    constexpr std::array<ShaderFileNameMapping, 7> vertexShaderFileNames =
    {{
        {ShaderId::Volume, "Volume.vert"},
        {ShaderId::SsaoInput, "SsaoInput.vert"},
        {ShaderId::Ssao, "Ssao.vert"},
        {ShaderId::SsaoBlur, "Ssao.vert"},
        {ShaderId::SsaoFinal, "SsaoFinal.vert"},
        {ShaderId::DebugQuad, "DebugQuad.vert"},
        {ShaderId::LightSource, "LightSource.vert"}
    }};

    constexpr std::array<ShaderFileNameMapping, 7> fragmentShaderFileNames =
    {{
        {ShaderId::Volume, "Volume.frag"},
        {ShaderId::SsaoInput, "SsaoInput.frag"},
        {ShaderId::Ssao, "Ssao.frag"},
        {ShaderId::SsaoBlur, "SsaoBlur.frag"},
        {ShaderId::SsaoFinal, "SsaoFinal.frag"},
        {ShaderId::DebugQuad, "DebugQuadColor.frag"},
        {ShaderId::LightSource, "LightSource.frag"}
    }};
}

namespace ShaderSource
{
    std::string_view GetShaderFileName(ShaderId shaderId, ShaderType shaderType)
    {
        const auto& shaderFileNames = (shaderType == ShaderType::Vertex) ? vertexShaderFileNames : fragmentShaderFileNames;

        const auto it = std::find_if(shaderFileNames.begin(), shaderFileNames.end(),
            [shaderId](const ShaderFileNameMapping& mapping)
            {
                return mapping.shaderId == shaderId;
            });

        if (it == shaderFileNames.end())
        {
            throw std::runtime_error{"Unknown shader ID"};
        }

        return it->fileName;
    }
}
