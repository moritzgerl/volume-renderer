#ifndef PARSE_GUI_PARAMETER_H
#define PARSE_GUI_PARAMETER_H

#include <data/ApplicationStateIniFileLoadingError.h>
#include <data/ApplicationStateIniFileSection.h>
#include <data/ApplicationStateIniFileKey.h>
#include <gui/GuiParameters.h>
#include <string_view>

namespace Parsing
{   
    // TODO find a better return type
    bool ParseGuiParameter(
        Data::ApplicationStateIniFileSection section,
        Data::ApplicationStateIniFileKey key,
        unsigned int elementIndex,
        std::string_view valueString,
        GuiParameters& guiParameters);
}

#endif
