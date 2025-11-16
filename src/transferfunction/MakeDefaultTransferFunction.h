/**
* \file MakeDefaultTransferFunction.h
*
* \brief Factory function for creating a transfer function with default control points.
*/

#ifndef MAKE_DEFAULT_TRANSFER_FUNCTION_H
#define MAKE_DEFAULT_TRANSFER_FUNCTION_H

#include <transferfunction/TransferFunction.h>

namespace Factory
{
    /**
    * Creates a transfer function with default control points.
    *
    * Constructs a TransferFunction object initialized with a set of default
    * control points that map scalar values to colors and opacity. The default
    * transfer function provides a reasonable starting point for visualizing
    * volumetric data with appropriate color mapping and transparency.
    *
    * @return TransferFunction object with default control points.
    *
    * @see TransferFunction for transfer function implementation.
    * @see TransferFunctionControlPoint for control point structure.
    * @see InterpolateTransferFunction for interpolation between control points.
    */
    TransferFunction MakeDefaultTransferFunction();
}

#endif
