/**
* \file ParseTransferFunctionControlPoint.h
*
* \brief Function for parsing transfer function control points from INI file values.
*/

#ifndef PARSE_TRANSFER_FUNCTION_POINT_H
#define PARSE_TRANSFER_FUNCTION_POINT_H

#include <persistence/ApplicationStateIniFileLoadingError.h>
#include <persistence/ApplicationStateIniFileKey.h>
#include <transferfunction/TransferFunctionControlPoint.h>

#include <expected>
#include <string_view>

namespace Persistence
{
    /**
    * Parses and applies a transfer function control point parameter.
    *
    * Converts the string value to the appropriate type based on the parameter
    * key and updates the corresponding field in the TransferFunctionControlPoint
    * structure. Supported parameters include scalar value, color components
    * (ColorR, ColorG, ColorB), and opacity. Returns an error if the value
    * cannot be parsed or is invalid.
    *
    * @param key The parameter key identifying which control point field to update.
    * @param valueString The string value to parse.
    * @param point The transfer function control point to update.
    * @return Expected containing either void on success or an error code on failure.
    *
    * @see TransferFunctionControlPoint for control point structure.
    * @see ApplicationStateIniFileKey for parameter key identifiers.
    * @see ApplicationStateIniFileLoadingError for error codes.
    */
    std::expected<void, ApplicationStateIniFileLoadingError> ParseTransferFunctionControlPoint(
        ApplicationStateIniFileKey key,
        std::string_view valueString,
        TransferFunctionControlPoint& point);
}

#endif
