#ifndef SAVE_STATE_LOADING_ERROR_H
#define SAVE_STATE_LOADING_ERROR_H

namespace Data
{
    enum class SaveStateLoadingError
    {
        FileNotFound,
        CannotOpenFile,
        ParseError
    };
}

#endif
