#ifndef TRANSFER_FUNCTION_H
#define TRANSFER_FUNCTION_H

#include <transferfunction/TransferFunctionControlPoint.h>

#include <config/TransferFunctionConstants.h>

#include <array>

class TransferFunction
{
public:
    size_t GetNumActivePoints() const;
    void SetNumActivePoints(size_t count);
    void IncrementNumActivePoints();

    const std::array<TransferFunctionControlPoint, TransferFunctionConstants::maxNumControlPoints>& GetControlPoints() const;
    std::array<TransferFunctionControlPoint, TransferFunctionConstants::maxNumControlPoints>& GetControlPoints();

    const TransferFunctionControlPoint& operator[](size_t index) const;
    TransferFunctionControlPoint& operator[](size_t index);

private:
    std::array<TransferFunctionControlPoint, TransferFunctionConstants::maxNumControlPoints> m_controlPoints;
    size_t m_numActivePoints;
};

#endif
