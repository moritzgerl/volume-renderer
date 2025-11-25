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

#include <string_view>

namespace ShaderSource
{
    /**
    * Returns a string_view to the cached shader source code for the given shader type.
    * Shader sources are loaded from disk once on first access and cached in static storage.
    *
    * @param shaderId The shader identifier (e.g., ShaderId::Volume)
    * @param shaderType The type of shader (ShaderType::Vertex or ShaderType::Fragment)
    * @return A string_view to the cached shader source code
    */
    std::string_view GetShaderSource(ShaderId shaderId, ShaderType shaderType);
}

#endif
