#ifndef GUI_PARAMETERS_LOADING_ERROR_H
#define GUI_PARAMETERS_LOADING_ERROR_H

namespace Data
{
    enum class GuiParametersLoadingError
    {
        FileNotFound,
        CannotOpenFile,
        ParseError
    };
}

#endif
