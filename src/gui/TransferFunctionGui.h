#ifndef TRANSFER_FUNCTION_GUI_H
#define TRANSFER_FUNCTION_GUI_H

#include <imgui.h>

struct GuiUpdateFlags;
class TransferFunction;

class TransferFunctionGui
{
public:
    TransferFunctionGui(TransferFunction& transferFunction, GuiUpdateFlags& guiUpdateFlags);
    void Update();

private:
    void UpdateState();
    void HandleInteraction();
    void Draw();

private:
    bool m_isHovered;
    bool m_isActive;
    bool m_wasClicked;
    size_t m_numActivePoints;
    int m_draggedPointIndex;
    int m_colorPickerPointIndex;
    int m_hoveredPointIndex;
    float m_interactiveAreaHeight;
    float m_gradientHeight;
    ImVec2 m_plotSize;
    ImVec2 m_plotPos;
    ImVec2 m_mousePos;
    TransferFunction& m_transferFunction;
    GuiUpdateFlags& m_guiUpdateFlags;
};

#endif
