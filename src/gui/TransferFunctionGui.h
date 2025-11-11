#ifndef TRANSFER_FUNCTION_GUI_H
#define TRANSFER_FUNCTION_GUI_H

struct GuiUpdateFlags;
class TransferFunction;

namespace TransferFunctionGui
{
    void Draw(TransferFunction& transferFunction, GuiUpdateFlags& guiUpdateFlags);
}

#endif
