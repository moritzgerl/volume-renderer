/**
* \file TransferFunction.h
*
* \brief Transfer function for mapping scalar values to colors and opacity.
*/

#ifndef TRANSFER_FUNCTION_H
#define TRANSFER_FUNCTION_H

#include <transferfunction/TransferFunctionControlPoint.h>

#include <config/TransferFunctionConstants.h>

#include <array>

/**
* \class TransferFunction
*
* \brief Manages control points for volume rendering transfer function.
*
* A transfer function maps scalar volume values to RGBA colors and opacity values.
* It is defined by a set of control points that are interpolated to create a smooth
* mapping. The transfer function is stored as a 1D texture and sampled in the volume
* rendering shader.
*
* Control points can be added, removed, and modified interactively via the GUI.
* When control points change, TransferFunctionTextureUpdater regenerates the 1D texture.
*
* @see TransferFunctionControlPoint for control point data structure.
* @see InterpolateTransferFunction for interpolating between control points.
* @see TransferFunctionTextureUpdater for updating the 1D texture when control points change.
* @see TransferFunctionGui for interactive editing in the GUI.
* @see TransferFunctionConstants for maximum number of control points.
*/
class TransferFunction
{
public:
    size_t GetNumActivePoints() const;
    void SetNumActivePoints(size_t count);
    void IncrementNumActivePoints();

    const std::array<TransferFunctionControlPoint, TransferFunctionConstants::maxNumControlPoints>& GetControlPoints() const;
    std::array<TransferFunctionControlPoint, TransferFunctionConstants::maxNumControlPoints>& GetControlPoints();

    /**
    * Access control point by index.
    * @param index The control point index.
    * @return const TransferFunctionControlPoint& The control point at the specified index.
    */
    const TransferFunctionControlPoint& operator[](size_t index) const;
    TransferFunctionControlPoint& operator[](size_t index);

    /**
    * Adds a new control point to the transfer function.
    * @param value The scalar value (0.0 to 1.0) for this control point.
    * @param opacity The opacity (0.0 to 1.0) for this control point.
    * @return void
    */
    void AddPoint(float value, float opacity);

    /**
    * Removes a control point from the transfer function.
    * @param index The index of the control point to remove.
    * @return void
    */
    void RemovePoint(size_t index);

private:
    std::array<TransferFunctionControlPoint, TransferFunctionConstants::maxNumControlPoints> m_controlPoints; /**< Array of transfer function control points. */
    size_t m_numActivePoints; /**< Number of currently active control points. */
};

#endif
