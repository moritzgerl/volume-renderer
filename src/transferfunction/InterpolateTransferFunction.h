/**
* \file InterpolateTransferFunction.h
*
* \brief Transfer function interpolation for generating continuous texture data.
*/

#ifndef INTERPOLATE_TRANSFER_FUNCTION_H
#define INTERPOLATE_TRANSFER_FUNCTION_H

#include <transferfunction/TransferFunctionControlPoint.h>

#include <glm/glm.hpp>
#include <span>

/**
* Evaluates the transfer function at a given normalized value.
*
* Interpolates between control points to generate smooth color and opacity
* transitions. Uses Catmull-Rom spline interpolation for opacity (smooth curves)
* and linear interpolation for color (to preserve color accuracy).
*
* This function is called repeatedly to generate a 1D texture that maps scalar
* values to RGBA colors for volume rendering.
*
* @param normalizedValue Scalar value in range [0, 1] to evaluate.
* @param activePoints Span of active control points, sorted by value.
* @return Interpolated RGBA color as vec4(rgb, opacity).
*
* @see TransferFunctionControlPoint for control point structure.
* @see TransferFunctionTextureUpdater for texture generation.
* @see TransferFunction for control point management.
*/
glm::vec4 InterpolateTransferFunction(
    float normalizedValue,
    std::span<const TransferFunctionControlPoint> activePoints
);

#endif
