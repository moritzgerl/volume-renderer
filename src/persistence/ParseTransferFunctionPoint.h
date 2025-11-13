#ifndef PARSE_TRANSFER_FUNCTION_CONTROL_POINT_H
#define PARSE_TRANSFER_FUNCTION_CONTROL_POINT_H

#include <persistence/ApplicationStateIniFileLoadingError.h>
#include <persistence/ApplicationStateIniFileKey.h>
#include <transferfunction/TransferFunctionControlPoint.h>
#include <expected>
#include <string_view>

namespace Persistence
{   
    std::expected<TransferFunctionControlPoint, ApplicationStateIniFileLoadingError> ParseTransferFunctionControlPoint(
        ApplicationStateIniFileKey applicationStateIniFileKey,
        std::string_view valueString);
}

#endif
