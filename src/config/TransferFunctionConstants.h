/**
* \file TransferFunctionConstants.h
*
* \brief Compile-time constants for transfer function configuration.
*/

#ifndef TRANSFER_FUNCTION_CONSTANTS_H
#define TRANSFER_FUNCTION_CONSTANTS_H

#include <cstddef>

/**
* \namespace TransferFunctionConstants
*
* \brief Configuration constants for transfer function limits and texture sizes.
*
* Defines compile-time constants that control transfer function behavior,
* including the maximum number of control points and the resolution of the
* 1D texture used for GPU sampling.
*
* @see TransferFunction for control point management.
* @see TransferFunctionTextureUpdater for texture generation.
* @see InterpolateTransferFunction for texture data interpolation.
*/
namespace TransferFunctionConstants
{
    constexpr size_t maxNumControlPoints = 8;    /**< Maximum number of transfer function control points. */
    constexpr size_t textureSize = 512;          /**< Resolution of the 1D transfer function texture in texels. */
    constexpr size_t textureDataSize = textureSize * 4;  /**< Size of texture data buffer in bytes (RGBA format). */
}

#endif
