#ifndef LOAD_SAVE_STATE_FROM_INI_H
#define LOAD_SAVE_STATE_FROM_INI_H

#include <data/SaveState.h>
#include <data/SaveStateLoadingError.h>

#include <expected>
#include <filesystem>

namespace Data
{
    std::expected<SaveState, SaveStateLoadingError> LoadSaveStateFromIni(const std::filesystem::path& iniFilePath);
}

#endif
