#ifndef GET_APPLICATION_STATE_INI_FILE_KEY_H
#define GET_APPLICATION_STATE_INI_FILE_KEY_H

#include <data/ApplicationStateIniFileKey.h>
#include <string_view>

namespace Data
{
    ApplicationStateIniFileKey GetApplicationStateIniFileKey(std::string_view key);
}

#endif
