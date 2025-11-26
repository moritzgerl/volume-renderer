/**
* \file GetShaderFileExtension.h
*
* \brief Maps shader types to their file extensions.
*/

#ifndef GET_SHADER_FILE_EXTENSION_H
#define GET_SHADER_FILE_EXTENSION_H

#include <shader/ShaderLoadingError.h>
#include <shader/ShaderType.h>

#include <expected>
#include <string_view>

namespace ShaderSource
{
    /**
    * Returns the file extension for a given shader type.
    *
    * @param shaderType The type of shader (ShaderType::Vertex or ShaderType::Fragment)
    * @return The file extension (e.g., ".vert" or ".frag") on success, or a ShaderLoadingError on failure
    */
    std::expected<std::string_view, ShaderLoadingError> GetShaderFileExtension(ShaderType shaderType);
}

#endif
