#ifndef PERSIST_SAVE_STATE_TO_INI_H
#define PERSIST_SAVE_STATE_TO_INI_H

#include <data/SaveState.h>
#include <data/SaveStateSavingError.h>

#include <expected>
#include <filesystem>

namespace Data
{
    std::expected<void, SaveStateSavingError> PersistSaveStateToIni(const SaveState& saveState, const std::filesystem::path& iniFilePath);
}

#endif
