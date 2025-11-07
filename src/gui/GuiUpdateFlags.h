#ifndef GUI_UPDATE_FLAGS_H
#define GUI_UPDATE_FLAGS_H

struct GuiUpdateFlags
{
    GuiUpdateFlags()
    {
        ssaoParametersChanged = false;
        transferFunctionChanged = false;
    };

    bool ssaoParametersChanged;
    bool transferFunctionChanged;
};

#endif
