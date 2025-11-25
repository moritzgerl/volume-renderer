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
    * Returns the base file name (without extension) for a given shader ID and type.
    *
    * @param shaderId The shader identifier (e.g., ShaderId::Volume)
    * @return The base file name without extension (e.g., "Volume", "DebugQuadColor")
    * @throws std::runtime_error if the shader ID is unknown
    */
    std::string_view GetShaderFileName(ShaderId shaderId);
}

#endif
