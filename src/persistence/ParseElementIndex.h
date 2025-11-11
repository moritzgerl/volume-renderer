#ifndef PARSE_ELEMENT_INDEX_H
#define PARSE_ELEMENT_INDEX_H

#include <persistence/ApplicationStateIniFileSection.h>
#include <persistence/ApplicationStateIniFileLoadingError.h>
#include <expected>
#include <string_view>

namespace Parsing
{   
    std::expected<unsigned int, Data::ApplicationStateIniFileLoadingError> ParseElementIndex(const std::string_view line, Data::ApplicationStateIniFileSection currentSection);
}

#endif
