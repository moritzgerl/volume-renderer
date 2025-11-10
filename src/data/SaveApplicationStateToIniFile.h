#ifndef SAVE_APPLICATION_STATE_TO_INI_FILE_H
#define SAVE_APPLICATION_STATE_TO_INI_FILE_H

#include <data/ApplicationState.h>
#include <data/ApplicationStateIniFileSavingError.h>

#include <expected>
#include <filesystem>

namespace Data
{
    std::expected<void, ApplicationStateIniFileSavingError> SaveApplicationStateToIniFile(const ApplicationState& applicationState, const std::filesystem::path& iniFilePath);
}

#endif
