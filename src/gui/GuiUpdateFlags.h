#ifndef GUI_UPDATE_FLAGS_H
#define GUI_UPDATE_FLAGS_H

struct GuiUpdateFlags
{
    GuiUpdateFlags()
    {
        ssaoParametersChanged = false;
    };

    bool ssaoParametersChanged;    
};

#endif
