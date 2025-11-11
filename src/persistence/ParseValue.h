#ifndef PARSE_VALUE_H
#define PARSE_VALUE_H

#include <persistence/ApplicationStateIniFileLoadingError.h>
#include <expected>
#include <string_view>

namespace Persistence
{   
    template<typename T>
    using ParseValueResult = std::expected<T, ApplicationStateIniFileLoadingError>;

    template<typename T>
    ParseValueResult<T> ParseValue(const std::string_view string);
}

#endif
