#ifndef LOAD_APPLICATION_STATE_FROM_INI_FILE_H
#define LOAD_APPLICATION_STATE_FROM_INI_FILE_H

#include <persistence/ApplicationState.h>
#include <persistence/ApplicationStateIniFileLoadingError.h>

#include <expected>
#include <filesystem>

namespace Persistence
{
    std::expected<ApplicationState, ApplicationStateIniFileLoadingError> LoadApplicationStateFromIniFile(const std::filesystem::path& iniFilePath);
}

#endif
