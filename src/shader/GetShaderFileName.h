/**
* \file GetShaderFileName.h
*
* \brief Maps shader IDs to their corresponding shader file names.
*/

#ifndef GET_SHADER_FILE_NAME_H
#define GET_SHADER_FILE_NAME_H

#include <shader/ShaderId.h>
#include <shader/ShaderType.h>

#include <string_view>

namespace ShaderSource
{
    /**
    * Returns the file name for a given shader ID and type.
    *
    * @param shaderId The shader identifier (e.g., ShaderId::Volume)
    * @param shaderType The type of shader (ShaderType::Vertex or ShaderType::Fragment)
    * @return The file name of the shader (e.g., "Volume.vert" or "Volume.frag")
    * @throws std::runtime_error if the shader ID is unknown
    */
    std::string_view GetShaderFileName(ShaderId shaderId, ShaderType shaderType);
}

#endif
