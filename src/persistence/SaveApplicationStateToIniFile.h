/**
* \file SaveApplicationStateToIniFile.h
*
* \brief Function for saving application state to an INI file.
*/

#ifndef SAVE_APPLICATION_STATE_TO_INI_FILE_H
#define SAVE_APPLICATION_STATE_TO_INI_FILE_H

#include <persistence/ApplicationState.h>
#include <persistence/ApplicationStateIniFileSavingError.h>

#include <expected>
#include <filesystem>

namespace Persistence
{
    /**
    * Saves application state to an INI file.
    *
    * Serializes application state including camera parameters, GUI parameters,
    * and transfer function control points to an INI file format. The function
    * writes each state component to separate sections with key-value pairs for
    * each parameter. Returns an error if the file cannot be created or written.
    *
    * @param applicationState The application state to save.
    * @param iniFilePath Path to the INI file to create/overwrite.
    * @return Expected containing either void on success or an error code on failure.
    *
    * @see ApplicationState for state structure.
    * @see ApplicationStateIniFileSavingError for error codes.
    * @see LoadApplicationStateFromIniFile for loading state.
    */
    std::expected<void, ApplicationStateIniFileSavingError> SaveApplicationStateToIniFile(const ApplicationState& applicationState, const std::filesystem::path& iniFilePath);
}

#endif
