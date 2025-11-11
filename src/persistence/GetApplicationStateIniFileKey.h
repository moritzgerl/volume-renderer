#ifndef GET_APPLICATION_STATE_INI_FILE_KEY_H
#define GET_APPLICATION_STATE_INI_FILE_KEY_H

#include <persistence/ApplicationStateIniFileKey.h>
#include <string_view>

namespace Persistence
{
    ApplicationStateIniFileKey GetApplicationStateIniFileKey(std::string_view key);
}

#endif
