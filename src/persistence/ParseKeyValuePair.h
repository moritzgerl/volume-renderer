#ifndef PARSE_KEY_VALUE_PAIR_H
#define PARSE_KEY_VALUE_PAIR_H

#include <persistence/ApplicationStateIniFileLoadingError.h>
#include <persistence/KeyValuePair.h>

#include <expected>
#include <string_view>

namespace Persistence
{
    std::expected<KeyValuePair, ApplicationStateIniFileLoadingError> ParseKeyValuePair(std::string_view line);
}

#endif
