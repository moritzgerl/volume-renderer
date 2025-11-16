/**
* \file LoadApplicationStateFromIniFile.h
*
* \brief Function for loading application state from an INI file.
*/

#ifndef LOAD_APPLICATION_STATE_FROM_INI_FILE_H
#define LOAD_APPLICATION_STATE_FROM_INI_FILE_H

#include <persistence/ApplicationState.h>
#include <persistence/ApplicationStateIniFileLoadingError.h>

#include <expected>
#include <filesystem>

namespace Persistence
{
    /**
    * Loads application state from an INI file.
    *
    * Parses an INI file containing serialized application state including camera
    * parameters, GUI parameters, and transfer function control points. The function
    * reads each section of the INI file, parses key-value pairs, and constructs
    * the corresponding state structures. Returns an error if the file cannot be
    * opened, parsed, or contains invalid data.
    *
    * @param iniFilePath Path to the INI file to load.
    * @return Expected containing either the loaded ApplicationState or an error code.
    *
    * @see ApplicationState for state structure.
    * @see ApplicationStateIniFileLoadingError for error codes.
    * @see SaveApplicationStateToIniFile for saving state.
    */
    std::expected<ApplicationState, ApplicationStateIniFileLoadingError> LoadApplicationStateFromIniFile(const std::filesystem::path& iniFilePath);
}

#endif
