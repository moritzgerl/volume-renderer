#ifndef TRANSFER_FUNCTION_GUI_H
#define TRANSFER_FUNCTION_GUI_H

struct GuiParameters;
struct GuiUpdateFlags;

namespace TransferFunctionGui
{
    void Draw(GuiParameters& guiParameters, GuiUpdateFlags& guiUpdateFlags);
}

#endif
