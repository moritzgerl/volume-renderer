/**
* \file ShaderLoadingError.h
*
* \brief Defines error codes for shader loading operations.
*/

#ifndef SHADER_LOADING_ERROR_H
#define SHADER_LOADING_ERROR_H

enum class ShaderLoadingError
{
    UnknownShaderType,
    UnknownShaderId,
    FileOpenFailed
};

#endif
