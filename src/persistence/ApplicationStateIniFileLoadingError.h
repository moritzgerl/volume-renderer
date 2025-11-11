#ifndef APPLICATION_STATE_INI_FILE_LOADING_ERROR_H
#define APPLICATION_STATE_INI_FILE_LOADING_ERROR_H

namespace Data
{
    enum class ApplicationStateIniFileLoadingError
    {
        FileNotFound,
        CannotOpenFile,
        ParseError
    };
}

#endif
