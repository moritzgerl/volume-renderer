/**
* \file GetShaderSource.h
*
* \brief Provides access to shader source code via file loading with caching.
*
* Uses std::source_location to resolve shader file paths relative to this source file.
* Shader sources are loaded once and cached, then served as string_view references.
*/

#ifndef GET_SHADER_SOURCE_H
#define GET_SHADER_SOURCE_H

#include <shader/ShaderId.h>
#include <shader/ShaderType.h>

#include <string>

namespace ShaderSource
{
    /**
    * Loads and returns the shader source code for the given shader type.
    * Shader sources are loaded from disk each time this function is called.
    *
    * @param shaderId The shader identifier (e.g., ShaderId::Volume)
    * @param shaderType The type of shader (ShaderType::Vertex or ShaderType::Fragment)
    * @return The shader source code as a string
    */
    std::string GetShaderSource(ShaderId shaderId, ShaderType shaderType);
}

#endif
