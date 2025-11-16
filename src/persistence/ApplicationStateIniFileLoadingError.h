/**
* \file ApplicationStateIniFileLoadingError.h
*
* \brief Error codes for application state INI file loading operations.
*/

#ifndef APPLICATION_STATE_INI_FILE_LOADING_ERROR_H
#define APPLICATION_STATE_INI_FILE_LOADING_ERROR_H

namespace Persistence
{
    /**
    * \enum ApplicationStateIniFileLoadingError
    *
    * \brief Error codes returned when loading application state from INI files.
    *
    * Enumerates the possible errors that can occur during INI file loading
    * including file access errors and parsing failures.
    */
    enum class ApplicationStateIniFileLoadingError
    {
        FileNotFound,      /**< The specified INI file does not exist. */
        CannotOpenFile,    /**< The INI file exists but cannot be opened for reading. */
        ParseError         /**< The INI file contains invalid syntax or malformed data. */
    };
}

#endif
