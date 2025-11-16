/**
* \file ApplicationStateIniFileSavingError.h
*
* \brief Error codes for application state INI file saving operations.
*/

#ifndef APPLICATION_STATE_INI_FILE_SAVING_ERROR_H
#define APPLICATION_STATE_INI_FILE_SAVING_ERROR_H

namespace Persistence
{
    /**
    * \enum ApplicationStateIniFileSavingError
    *
    * \brief Error codes returned when saving application state to INI files.
    *
    * Enumerates the possible errors that can occur during INI file saving
    * including file creation and writing failures.
    */
    enum class ApplicationStateIniFileSavingError
    {
        CannotOpenFile,    /**< The INI file cannot be created or opened for writing. */
        WriteError         /**< An error occurred while writing data to the INI file. */
    };
}

#endif
