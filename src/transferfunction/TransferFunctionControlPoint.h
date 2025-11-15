/**
* \file TransferFunctionControlPoint.h
*
* \brief Control point structure for transfer function definition.
*/

#ifndef TRANSFER_FUNCTION_CONTROL_POINT_H
#define TRANSFER_FUNCTION_CONTROL_POINT_H

#include <glm/glm.hpp>

/**
* \struct TransferFunctionControlPoint
*
* \brief Defines a single control point in a transfer function.
*
* Represents a point on the transfer function curve that maps a scalar value
* to a color and opacity. Transfer functions use multiple control points that
* are interpolated to create smooth color and opacity transitions in volume rendering.
*
* The value field determines where the control point appears on the horizontal axis,
* while color and opacity determine the visual appearance of voxels at that scalar value.
*
* @see TransferFunction for managing collections of control points.
* @see TransferFunctionGui for interactive control point editing.
* @see InterpolateTransferFunction for generating continuous texture data.
*/
struct TransferFunctionControlPoint
{
    float value; /**< Scalar value in range [0, 1] representing position on transfer function. */
    glm::vec3 color; /**< RGB color components in range [0, 1]. */
    float opacity; /**< Opacity/alpha value in range [0, 1]. */
};

#endif
