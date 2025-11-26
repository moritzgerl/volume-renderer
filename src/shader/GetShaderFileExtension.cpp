#include <shader/GetShaderFileExtension.h>

#include <array>

namespace
{
    struct ShaderFileExtensionMapping
    {
        ShaderType shaderType;
        std::string_view shaderFileExtension;
    };

    constexpr std::array<ShaderFileExtensionMapping, 2> shaderFileExtensions =
    {{
        {ShaderType::Vertex, ".vert"},
        {ShaderType::Fragment, ".frag"}
    }};
}

namespace ShaderSource
{
    std::expected<std::string_view, ShaderLoadingError> GetShaderFileExtension(ShaderType shaderType)
    {
        for (const auto& mapping : shaderFileExtensions)
        {
            if (mapping.shaderType == shaderType)
            {
                return mapping.shaderFileExtension;
            }
        }

        return std::unexpected{ShaderLoadingError::UnknownShaderType};
    }
}
