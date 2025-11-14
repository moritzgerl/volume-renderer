#ifndef TRANSFER_FUNCTION_GUI_H
#define TRANSFER_FUNCTION_GUI_H

#include <imgui.h>

#include <optional>

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
    bool m_wasClicked;
    size_t m_numActivePoints;
    std::optional<size_t> m_draggedPointIndex;
    std::optional<size_t> m_colorPickerPointIndex;
    std::optional<size_t> m_hoveredPointIndex;
    float m_interactiveAreaHeight;
    float m_gradientHeight;
    ImVec2 m_plotSize;
    ImVec2 m_plotPos;
    ImVec2 m_mousePos;
    TransferFunction& m_transferFunction;
    GuiUpdateFlags& m_guiUpdateFlags;
};

#endif
