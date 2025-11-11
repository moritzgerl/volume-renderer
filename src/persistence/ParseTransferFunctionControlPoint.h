#ifndef PARSE_TRANSFER_FUNCTION_POINT_H
#define PARSE_TRANSFER_FUNCTION_POINT_H

#include <persistence/ApplicationStateIniFileLoadingError.h>
#include <persistence/ApplicationStateIniFileKey.h>
#include <gui/TransferFunctionControlPoint.h>
#include <expected>
#include <string_view>

namespace Persistence
{   
    // TODO find a better return type
    bool ParseTransferFunctionControlPoint(
        ApplicationStateIniFileKey key,
        std::string_view valueString,
        TransferFunctionControlPoint& point);
}

#endif
