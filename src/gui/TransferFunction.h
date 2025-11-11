#ifndef TRANSFER_FUNCTION_H
#define TRANSFER_FUNCTION_H

#include <gui/TransferFunctionControlPoint.h>

#include <array>

class TransferFunction
{
public:
    static constexpr size_t maxControlPoints = 8;

    TransferFunction();

    size_t GetNumActivePoints() const;
    void SetNumActivePoints(size_t count);
    void IncrementNumActivePoints();

    const std::array<TransferFunctionControlPoint, maxControlPoints>& GetControlPoints() const;
    std::array<TransferFunctionControlPoint, maxControlPoints>& GetControlPoints();

    const TransferFunctionControlPoint& operator[](size_t index) const;
    TransferFunctionControlPoint& operator[](size_t index);

private:
    std::array<TransferFunctionControlPoint, maxControlPoints> m_controlPoints;
    size_t m_numActivePoints;
};

#endif
