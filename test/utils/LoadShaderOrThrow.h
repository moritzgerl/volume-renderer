/**
* \file LoadShaderOrThrow.h
*
* \brief Test utility for loading shaders with exception handling.
*
* Provides a convenience function for test code to load shaders and throw
* exceptions on failure rather than handling std::expected return values.
*/

#ifndef LOAD_SHADER_OR_THROW_H
#define LOAD_SHADER_OR_THROW_H

#include <shader/ShaderId.h>
#include <shader/ShaderType.h>

#include <string>

namespace TestUtils
{
    /**
    * Loads a shader and returns its source code.
    * Throws std::runtime_error if loading fails.
    *
    * @param shaderId The shader identifier (e.g., ShaderId::Volume)
    * @param shaderType The type of shader (ShaderType::Vertex or ShaderType::Fragment)
    * @return The shader source code as a string
    * @throws std::runtime_error if shader loading fails
    */
    std::string LoadShaderOrThrow(ShaderId shaderId, ShaderType shaderType);
}

#endif
