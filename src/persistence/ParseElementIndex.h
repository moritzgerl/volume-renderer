#ifndef PARSE_ELEMENT_INDEX_H
#define PARSE_ELEMENT_INDEX_H

#include <persistence/ApplicationStateIniFileSection.h>
#include <persistence/ApplicationStateIniFileLoadingError.h>
#include <expected>
#include <string_view>

namespace Persistence
{   
    std::expected<unsigned int, ApplicationStateIniFileLoadingError> ParseElementIndex(const std::string_view line, ApplicationStateIniFileSection currentSection);
}

#endif
