/**
* \file ParseKeyValuePair.h
*
* \brief Function for parsing key-value pairs from INI file lines.
*/

#ifndef PARSE_KEY_VALUE_PAIR_H
#define PARSE_KEY_VALUE_PAIR_H

#include <persistence/ApplicationStateIniFileLoadingError.h>
#include <persistence/KeyValuePair.h>

#include <expected>
#include <string_view>

namespace Persistence
{
    /**
    * Parses a key-value pair from an INI file line.
    *
    * Extracts the key and value from a line in the format "key = value",
    * handling whitespace trimming around the '=' separator. Returns an
    * error if the line does not contain a valid key-value pair format.
    *
    * @param line The INI file line to parse.
    * @return Expected containing either the parsed KeyValuePair or an error code.
    *
    * @see KeyValuePair for the parsed key-value structure.
    * @see ApplicationStateIniFileLoadingError for error codes.
    */
    std::expected<KeyValuePair, ApplicationStateIniFileLoadingError> ParseKeyValuePair(std::string_view line);
}

#endif
