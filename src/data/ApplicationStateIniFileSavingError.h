#ifndef APPLICATION_STATE_INI_FILE_SAVING_ERROR_H
#define APPLICATION_STATE_INI_FILE_SAVING_ERROR_H

namespace Data
{
    enum class ApplicationStateIniFileSavingError
    {
        CannotOpenFile,
        WriteError
    };
}

#endif
