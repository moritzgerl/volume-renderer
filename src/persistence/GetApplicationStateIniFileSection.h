/**
* \file GetApplicationStateIniFileSection.h
*
* \brief Function for converting string sections to ApplicationStateIniFileSection enum values.
*/

#ifndef GET_APPLICATION_STATE_INI_FILE_SECTION_H
#define GET_APPLICATION_STATE_INI_FILE_SECTION_H

#include <persistence/ApplicationStateIniFileSection.h>
#include <string_view>

namespace Persistence
{
    /**
    * Converts a string section name to an ApplicationStateIniFileSection enum value.
    *
    * Maps INI file section header strings (e.g., "Camera", "SSAO", "PointLight")
    * to their corresponding enum values for type-safe section identification.
    * Returns ApplicationStateIniFileSection::None if the section string is not
    * recognized.
    *
    * @param section The section name string from the INI file header.
    * @return The corresponding ApplicationStateIniFileSection enum value.
    *
    * @see ApplicationStateIniFileSection for section enumeration.
    */
    ApplicationStateIniFileSection GetApplicationStateIniFileSection(std::string_view section);
}

#endif
