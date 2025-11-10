#ifndef PARSE_ELEMENT_INDEX_H
#define PARSE_ELEMENT_INDEX_H

#include <data/ApplicationStateIniFileSection.h>
#include <data/ApplicationStateIniFileLoadingError.h>
#include <expected>
#include <string_view>

namespace Parsing
{   
    std::expected<unsigned int, Data::ApplicationStateIniFileLoadingError> ParseElementIndex(const std::string_view line, Data::ApplicationStateIniFileSection currentSection);
}

#endif
