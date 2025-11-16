/**
* \file ParseValue.h
*
* \brief Template function for parsing typed values from string views.
*/

#ifndef PARSE_VALUE_H
#define PARSE_VALUE_H

#include <persistence/ApplicationStateIniFileLoadingError.h>
#include <expected>
#include <string_view>

namespace Persistence
{
    /**
    * \typedef ParseValueResult
    *
    * \brief Result type for value parsing operations.
    *
    * @tparam T The type of value being parsed.
    */
    template<typename T>
    using ParseValueResult = std::expected<T, ApplicationStateIniFileLoadingError>;

    /**
    * Parses a typed value from a string view.
    *
    * Converts a string representation to the specified type. Supported types
    * include fundamental types (int, unsigned int, float, bool) and glm vector
    * types. Returns an error if the string cannot be converted to the requested
    * type due to invalid format or out-of-range values.
    *
    * @tparam T The type to parse the value into.
    * @param string The string view containing the value to parse.
    * @return Expected containing either the parsed value or an error code.
    *
    * @see ApplicationStateIniFileLoadingError for error codes.
    */
    template<typename T>
    ParseValueResult<T> ParseValue(const std::string_view string);
}

#endif
