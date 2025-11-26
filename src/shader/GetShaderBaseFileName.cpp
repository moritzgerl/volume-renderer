#include <shader/GetShaderBaseFileName.h>

#include <algorithm>
#include <array>

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
    std::expected<std::string_view, ShaderLoadingError> GetShaderBaseFileName(ShaderId shaderId)
    {
        const auto it = std::find_if(shaderBaseFileNames.begin(), shaderBaseFileNames.end(),
            [shaderId](const ShaderBaseFileNameMapping& mapping)
            {
                return mapping.shaderId == shaderId;
            });

        if (it == shaderBaseFileNames.end())
        {
            return std::unexpected{ShaderLoadingError::UnknownShaderId};
        }

        return it->shaderBaseFileName;
    }
}
