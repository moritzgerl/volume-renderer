/**
* \file ParseElementIndex.h
*
* \brief Function for parsing element indices from INI file section headers.
*/

#ifndef PARSE_ELEMENT_INDEX_H
#define PARSE_ELEMENT_INDEX_H

#include <persistence/ApplicationStateIniFileSection.h>
#include <persistence/ApplicationStateIniFileLoadingError.h>
#include <expected>
#include <string_view>

namespace Persistence
{
    /**
    * Parses an element index from an indexed section header.
    *
    * Extracts the numeric index from section headers in the format
    * "[SectionName:Index]", used for indexed elements like point lights
    * and transfer function control points. Returns an error if the index
    * cannot be parsed or if the section type does not support indexing.
    *
    * @param line The INI file line containing the section header.
    * @param currentSection The section type being parsed.
    * @return Expected containing either the parsed index or an error code.
    *
    * @see ApplicationStateIniFileSection for section types.
    * @see ApplicationStateIniFileLoadingError for error codes.
    * @see ParseSectionHeader for extracting section identifiers.
    */
    std::expected<unsigned int, ApplicationStateIniFileLoadingError> ParseElementIndex(const std::string_view line, ApplicationStateIniFileSection currentSection);
}

#endif
