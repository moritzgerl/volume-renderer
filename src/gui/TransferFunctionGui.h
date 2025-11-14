#ifndef TRANSFER_FUNCTION_GUI_H
#define TRANSFER_FUNCTION_GUI_H

#include <imgui.h>

struct GuiUpdateFlags;
class TransferFunction;

class TransferFunctionGui
{
public:
    TransferFunctionGui(TransferFunction& transferFunction, GuiUpdateFlags& guiUpdateFlags);    
    void Draw();

private:
    void HandleInteraction();

private:
    bool m_isHovered{false};
    bool m_isActive{false};
    bool m_wasClicked{false};
    int m_draggedPointIndex{-1};
    int m_colorPickerPointIndex{-1};
    int m_hoveredPointIndex{-1};
    float m_gradientHeight{15.0f};
    ImVec2 m_plotSize{};
    ImVec2 m_plotPos{};
    ImVec2 m_mousePos{};
    TransferFunction& m_transferFunction;
    GuiUpdateFlags& m_guiUpdateFlags;
};

#endif
