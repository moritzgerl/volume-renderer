#ifndef PERSIST_GUI_PARAMETERS_TO_INI_H
#define PERSIST_GUI_PARAMETERS_TO_INI_H

#include <data/GuiParametersSavingError.h>
#include <gui/GuiParameters.h>

#include <expected>
#include <filesystem>

namespace Data
{
    std::expected<void, GuiParametersSavingError> PersistGuiParametersToIni(const GuiParameters& guiParameters, const std::filesystem::path& iniFilePath);
}

#endif
