#ifndef PARSE_TRANSFER_FUNCTION_POINT_H
#define PARSE_TRANSFER_FUNCTION_POINT_H

#include <persistence/ApplicationStateIniFileLoadingError.h>
#include <persistence/ApplicationStateIniFileKey.h>
#include <gui/TransferFunctionControlPoint.h>
#include <expected>
#include <string_view>

namespace Parsing
{   
    // TODO find a better return type
    bool ParseTransferFunctionControlPoint(
        Data::ApplicationStateIniFileKey key,
        std::string_view valueString,
        TransferFunctionControlPoint& point);
}

#endif
