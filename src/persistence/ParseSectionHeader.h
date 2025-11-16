/**
* \file ParseSectionHeader.h
*
* \brief Function for parsing section headers from INI file lines.
*/

#ifndef PARSE_SECTION_HEADER_H
#define PARSE_SECTION_HEADER_H

#include <persistence/ApplicationStateIniFileSection.h>
#include <string_view>

namespace Persistence
{
    /**
    * Parses a section header from an INI file line.
    *
    * Extracts the section name from a line in the format "[SectionName]" or
    * "[SectionName:Index]" (for indexed sections like point lights). Returns
    * the corresponding ApplicationStateIniFileSection enum value, or
    * ApplicationStateIniFileSection::None if the section is not recognized.
    *
    * @param line The INI file line containing the section header.
    * @return The parsed section identifier.
    *
    * @see ApplicationStateIniFileSection for section identifiers.
    * @see ParseElementIndex for extracting indices from indexed sections.
    */
    ApplicationStateIniFileSection ParseSectionHeader(std::string_view line);
}

#endif
