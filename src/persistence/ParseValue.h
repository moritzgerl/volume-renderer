#ifndef PARSE_VALUE_H
#define PARSE_VALUE_H

#include <persistence/ApplicationStateIniFileLoadingError.h>
#include <expected>
#include <string_view>

namespace Parsing
{   
    template<typename T>
    using ParseValueResult = std::expected<T, Data::ApplicationStateIniFileLoadingError>;

    template<typename T>
    ParseValueResult<T> ParseValue(const std::string_view string);
}

#endif
