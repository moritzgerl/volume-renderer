/**
* \file KeyValuePair.h
*
* \brief Structure representing a key-value pair from INI file parsing.
*/

#ifndef KEY_VALUE_PAIR_H
#define KEY_VALUE_PAIR_H

#include <string_view>

namespace Persistence
{
    /**
    * \struct KeyValuePair
    *
    * \brief Represents a parsed key-value pair from an INI file line.
    *
    * Contains string views to the key and value portions of an INI file
    * parameter line. String views reference the original line buffer,
    * avoiding unnecessary string allocations during parsing.
    */
    struct KeyValuePair
    {
        std::string_view key;    /**< The parameter key (left side of '='). */
        std::string_view value;  /**< The parameter value (right side of '='). */
    };
}

#endif
