#ifndef TRANSFER_FUNCTION_H
#define TRANSFER_FUNCTION_H

#include <input/TransferFunctionControlPoint.h>

#include <array>

struct TransferFunction
{
    static constexpr size_t maxControlPoints = 8;
    std::array<TransferFunctionControlPoint, maxControlPoints> controlPoints;
    size_t numActivePoints;
    bool enabled;
};

#endif
