#ifndef LOAD_APPLICATION_STATE_FROM_INI_FILE_H
#define LOAD_APPLICATION_STATE_FROM_INI_FILE_H

#include <data/ApplicationState.h>
#include <data/ApplicationStateIniFileLoadingError.h>

#include <expected>
#include <filesystem>

namespace Data
{
    std::expected<ApplicationState, ApplicationStateIniFileLoadingError> LoadApplicationStateFromIniFile(const std::filesystem::path& iniFilePath);
}

#endif
