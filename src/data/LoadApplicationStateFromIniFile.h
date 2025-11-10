#ifndef LOAD_APPLICATION_STATE_FROM_INI_FILE_H
#define LOAD_APPLICATION_STATE_FROM_INI_FILE_H

#include <data/ApplicationStateIniFileLoadingError.h>
#include <gui/GuiParameters.h>

#include <expected>
#include <filesystem>

namespace Data
{
    std::expected<GuiParameters, ApplicationStateIniFileLoadingError> LoadApplicationStateFromIniFile(const std::filesystem::path& iniFilePath);
}

#endif
