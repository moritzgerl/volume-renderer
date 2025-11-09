#ifndef STORE_SAVE_STATE_TO_INI_H
#define STORE_SAVE_STATE_TO_INI_H

#include <data/SaveState.h>
#include <data/SaveStateSavingError.h>

#include <expected>
#include <filesystem>

namespace Data
{
    std::expected<void, SaveStateSavingError> StoreSaveStateToIni(const std::filesystem::path& iniFilePath, const SaveState& saveState);
}

#endif
