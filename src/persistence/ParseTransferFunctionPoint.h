#ifndef PARSE_TRANSFER_FUNCTION_CONTROL_POINT_H
#define PARSE_TRANSFER_FUNCTION_CONTROL_POINT_H

#include <persistence/ApplicationStateIniFileLoadingError.h>
#include <persistence/ApplicationStateIniFileKey.h>
#include <gui/TransferFunctionControlPoint.h>
#include <expected>
#include <string_view>

namespace Parsing
{   
    std::expected<TransferFunctionControlPoint, Data::ApplicationStateIniFileLoadingError> ParseTransferFunctionControlPoint(
        Data::ApplicationStateIniFileKey applicationStateIniFileKey,
        std::string_view valueString);
}

#endif
