#include <shader/GetShaderFileExtension.h>

#include <array>
#include <stdexcept>

namespace
{
    struct ShaderFileExtensionMapping
    {
        ShaderType shaderType;
        std::string_view extension;
    };

    constexpr std::array<ShaderFileExtensionMapping, 2> shaderFileExtensions =
    {{
        {ShaderType::Vertex, ".vert"},
        {ShaderType::Fragment, ".frag"}
    }};
}

namespace ShaderSource
{
    std::string_view GetShaderFileExtension(ShaderType shaderType)
    {
        for (const auto& mapping : shaderFileExtensions)
        {
            if (mapping.shaderType == shaderType)
            {
                return mapping.extension;
            }
        }

        throw std::runtime_error{"Unknown shader type"};
    }
}
