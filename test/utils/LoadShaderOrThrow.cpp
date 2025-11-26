#include <utils/LoadShaderOrThrow.h>
#include <shader/LoadShader.h>

#include <stdexcept>

namespace TestUtils
{
    std::string LoadShaderOrThrow(ShaderId shaderId, ShaderType shaderType)
    {
        const auto result = ShaderSource::LoadShader(shaderId, shaderType);
        if (!result.has_value())
        {
            throw std::runtime_error{"Failed to load shader"};
        }
        return result.value();
    }
}
