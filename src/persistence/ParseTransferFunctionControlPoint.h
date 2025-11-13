#ifndef PARSE_TRANSFER_FUNCTION_POINT_H
#define PARSE_TRANSFER_FUNCTION_POINT_H

#include <persistence/ApplicationStateIniFileLoadingError.h>
#include <persistence/ApplicationStateIniFileKey.h>
#include <transferfunction/TransferFunctionControlPoint.h>

#include <expected>
#include <string_view>

namespace Persistence
{
    std::expected<void, ApplicationStateIniFileLoadingError> ParseTransferFunctionControlPoint(
        ApplicationStateIniFileKey key,
        std::string_view valueString,
        TransferFunctionControlPoint& point);
}

#endif
