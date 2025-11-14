#ifndef TRANSFER_FUNCTION_GUI_H
#define TRANSFER_FUNCTION_GUI_H

struct GuiUpdateFlags;
class TransferFunction;

struct ImVec2;

namespace TransferFunctionGui
{
    void HandleInteraction(TransferFunction& transferFunction, GuiUpdateFlags& guiUpdateFlags,
                          const ImVec2& plotSize, const ImVec2& plotPos, float gradientHeight);
    void Draw(TransferFunction& transferFunction, GuiUpdateFlags& guiUpdateFlags);
}

#endif
