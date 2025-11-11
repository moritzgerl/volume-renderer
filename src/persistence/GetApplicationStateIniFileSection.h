#ifndef GET_APPLICATION_STATE_INI_FILE_SECTION_H
#define GET_APPLICATION_STATE_INI_FILE_SECTION_H

#include <persistence/ApplicationStateIniFileSection.h>
#include <string_view>

namespace Persistence
{
    ApplicationStateIniFileSection GetApplicationStateIniFileSection(std::string_view section);
}

#endif
