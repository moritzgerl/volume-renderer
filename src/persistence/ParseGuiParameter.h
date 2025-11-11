#ifndef PARSE_GUI_PARAMETER_H
#define PARSE_GUI_PARAMETER_H

#include <persistence/ApplicationStateIniFileLoadingError.h>
#include <persistence/ApplicationStateIniFileSection.h>
#include <persistence/ApplicationStateIniFileKey.h>
#include <gui/GuiParameters.h>

#include <expected>
#include <string_view>

namespace Persistence
{
    std::expected<void, ApplicationStateIniFileLoadingError> ParseGuiParameter(
        ApplicationStateIniFileSection section,
        ApplicationStateIniFileKey key,
        unsigned int elementIndex,
        std::string_view valueString,
        GuiParameters& guiParameters);
}

#endif
