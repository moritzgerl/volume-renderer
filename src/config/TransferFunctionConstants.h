#ifndef TRANSFER_FUNCTION_CONSTANTS_H
#define TRANSFER_FUNCTION_CONSTANTS_H

#include <cstddef>

namespace TransferFunctionConstants
{
    constexpr size_t maxNumControlPoints = 8;
    constexpr size_t textureSize = 512;
    constexpr size_t textureDataSize = textureSize * 4;
}

#endif
