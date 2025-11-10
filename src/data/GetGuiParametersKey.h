#ifndef GET_GUI_PARAMETERS_KEY_H
#define GET_GUI_PARAMETERS_KEY_H

#include <data/GuiParametersKey.h>
#include <string_view>

namespace Data
{
    GuiParametersKey GetGuiParametersKey(std::string_view key);
}

#endif
