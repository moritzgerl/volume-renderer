#include <shader/GetShaderBaseFileName.h>

#include <algorithm>
#include <array>
#include <stdexcept>

namespace
{
    struct ShaderBaseFileNameMapping
    {
        ShaderId shaderId;
        std::string_view shaderBaseFileName;
    };

    constexpr std::array<ShaderBaseFileNameMapping, 7> shaderBaseFileNames =
    {{
        {ShaderId::Volume, "Volume"},
        {ShaderId::Ssao, "Ssao"},
        {ShaderId::SsaoBlur, "Ssao"},
        {ShaderId::SsaoFinal, "SsaoFinal"},
        {ShaderId::SsaoInput, "SsaoInput"},
        {ShaderId::DebugQuad, "DebugQuad"},
        {ShaderId::LightSource, "LightSource"}
    }};
}

namespace ShaderSource
{
    std::string_view GetShaderBaseFileName(ShaderId shaderId)
    {
        const auto it = std::find_if(shaderBaseFileNames.begin(), shaderBaseFileNames.end(),
            [shaderId](const ShaderBaseFileNameMapping& mapping)
            {
                return mapping.shaderId == shaderId;
            });

        if (it == shaderBaseFileNames.end())
        {
            throw std::runtime_error{"Unknown shader ID"};
        }

        return it->shaderBaseFileName;
    }
}
