#ifndef INTERPOLATE_TRANSFER_FUNCTION_H
#define INTERPOLATE_TRANSFER_FUNCTION_H

#include <transferfunction/TransferFunctionControlPoint.h>

#include <glm/glm.hpp>
#include <span>

// Evaluates the transfer function at a given normalized value [0, 1]
// using Catmull-Rom spline interpolation for opacity and linear interpolation for color.
// Returns interpolated RGBA as vec4(rgb, opacity).
glm::vec4 InterpolateTransferFunction(
    float normalizedValue,
    std::span<const TransferFunctionControlPoint> activePoints
);

#endif
