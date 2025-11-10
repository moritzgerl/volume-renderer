#ifndef SAVE_STATE_SAVING_ERROR_H
#define SAVE_STATE_SAVING_ERROR_H

namespace Data
{
    enum class SaveStateSavingError
    {
        CannotOpenFile,
        WriteError
    };
}

#endif
