#ifndef PARSE_SECTION_HEADER_H
#define PARSE_SECTION_HEADER_H

#include <data/ApplicationStateIniFileSection.h>
#include <string_view>

namespace Parsing
{   
    Data::ApplicationStateIniFileSection ParseSectionHeader(std::string_view line);
}

#endif
