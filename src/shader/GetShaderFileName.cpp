#include <shader/GetShaderFileName.h>

#include <algorithm>
#include <array>
#include <stdexcept>

namespace
{
    struct ShaderFileNameMapping
    {
        ShaderId shaderId;
        std::string_view shaderFileName;
    };

    constexpr std::array<ShaderFileNameMapping, 7> shaderFileNames =
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
    std::string_view GetShaderFileName(ShaderId shaderId)
    {

        const auto it = std::find_if(shaderFileNames.begin(), shaderFileNames.end(),
            [shaderId](const ShaderFileNameMapping& mapping)
            {
                return mapping.shaderId == shaderId;
            });

        if (it == shaderFileNames.end())
        {
            throw std::runtime_error{"Unknown shader ID"};
        }

        return it->shaderFileName;
    }
}
