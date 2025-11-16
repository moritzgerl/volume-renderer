/**
* \file ParseTransferFunctionPoint.h
*
* \brief Function for parsing individual transfer function control point fields.
*/

#ifndef PARSE_TRANSFER_FUNCTION_CONTROL_POINT_H
#define PARSE_TRANSFER_FUNCTION_CONTROL_POINT_H

#include <persistence/ApplicationStateIniFileLoadingError.h>
#include <persistence/ApplicationStateIniFileKey.h>
#include <transferfunction/TransferFunctionControlPoint.h>
#include <expected>
#include <string_view>

namespace Persistence
{
    /**
    * Parses a single field of a transfer function control point.
    *
    * Converts a string value to the appropriate type based on the parameter
    * key and returns a TransferFunctionControlPoint with the parsed field set.
    * This function is used during INI file parsing to build control points
    * field by field. Supported keys include Value, ColorR, ColorG, ColorB,
    * and Opacity.
    *
    * @param applicationStateIniFileKey The parameter key identifying which field to parse.
    * @param valueString The string value to parse.
    * @return Expected containing either the control point with parsed field or an error code.
    *
    * @see TransferFunctionControlPoint for control point structure.
    * @see ApplicationStateIniFileKey for parameter key identifiers.
    * @see ApplicationStateIniFileLoadingError for error codes.
    * @see LoadApplicationStateFromIniFile for loading complete control points.
    */
    std::expected<TransferFunctionControlPoint, ApplicationStateIniFileLoadingError> ParseTransferFunctionControlPoint(
        ApplicationStateIniFileKey applicationStateIniFileKey,
        std::string_view valueString);
}

#endif
