#ifndef LOAD_GUI_PARAMETERS_FROM_INI_H
#define LOAD_GUI_PARAMETERS_FROM_INI_H

#include <data/GuiParametersLoadingError.h>
#include <gui/GuiParameters.h>

#include <expected>
#include <filesystem>

namespace Data
{
    std::expected<GuiParameters, GuiParametersLoadingError> LoadGuiParametersFromIni(const std::filesystem::path& iniFilePath);
}

#endif
