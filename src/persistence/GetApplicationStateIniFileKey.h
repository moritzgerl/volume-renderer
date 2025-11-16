/**
* \file GetApplicationStateIniFileKey.h
*
* \brief Function for converting string keys to ApplicationStateIniFileKey enum values.
*/

#ifndef GET_APPLICATION_STATE_INI_FILE_KEY_H
#define GET_APPLICATION_STATE_INI_FILE_KEY_H

#include <persistence/ApplicationStateIniFileKey.h>
#include <string_view>

namespace Persistence
{
    /**
    * Converts a string key to an ApplicationStateIniFileKey enum value.
    *
    * Maps INI file parameter key strings (e.g., "PositionX", "SsaoRadius")
    * to their corresponding enum values for type-safe parameter identification.
    * Returns ApplicationStateIniFileKey::Unknown if the key string is not
    * recognized.
    *
    * @param key The parameter key string from the INI file.
    * @return The corresponding ApplicationStateIniFileKey enum value.
    *
    * @see ApplicationStateIniFileKey for parameter key enumeration.
    */
    ApplicationStateIniFileKey GetApplicationStateIniFileKey(std::string_view key);
}

#endif
