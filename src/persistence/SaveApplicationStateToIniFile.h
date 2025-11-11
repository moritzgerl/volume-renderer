#ifndef SAVE_APPLICATION_STATE_TO_INI_FILE_H
#define SAVE_APPLICATION_STATE_TO_INI_FILE_H

#include <persistence/ApplicationState.h>
#include <persistence/ApplicationStateIniFileSavingError.h>

#include <expected>
#include <filesystem>

namespace Persistence
{
    std::expected<void, ApplicationStateIniFileSavingError> SaveApplicationStateToIniFile(const ApplicationState& applicationState, const std::filesystem::path& iniFilePath);
}

#endif
