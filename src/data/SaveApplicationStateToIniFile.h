#ifndef SAVE_APPLICATION_STATE_TO_INI_FILE_H
#define SAVE_APPLICATION_STATE_TO_INI_FILE_H

#include <data/ApplicationStateIniFileSavingError.h>
#include <gui/GuiParameters.h>

#include <expected>
#include <filesystem>

namespace Data
{
    std::expected<void, ApplicationStateIniFileSavingError> SaveApplicationStateToIniFile(const GuiParameters& guiParameters, const std::filesystem::path& iniFilePath);
}

#endif
