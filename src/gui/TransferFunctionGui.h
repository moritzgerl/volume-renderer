/**
* \file TransferFunctionGui.h
*
* \brief Interactive transfer function editor widget for volume rendering.
*/

#ifndef TRANSFER_FUNCTION_GUI_H
#define TRANSFER_FUNCTION_GUI_H

#include <imgui.h>

#include <optional>

struct GuiUpdateFlags;
class TransferFunction;

/**
* \class TransferFunctionGui
*
* \brief ImGui widget for interactive transfer function editing.
*
* Provides an interactive editor for modifying transfer function control points
* that map scalar values to colors and opacity in volume rendering. Users can:
* - Add control points by double-clicking
* - Remove control points by right-clicking
* - Drag control points to adjust value/opacity
* - Change colors via color picker
*
* The widget displays a color gradient at the bottom and an opacity curve above it.
* Control points are shown as draggable circles. Mouse interactions are tracked to
* provide visual feedback (hover effects, cursor changes).
*
* When control points are modified, sets GuiUpdateFlags::transferFunctionChanged
* to trigger texture regeneration via TransferFunctionTextureUpdater.
*
* @see TransferFunction for control point storage and manipulation.
* @see GuiUpdateFlags for change notification.
* @see TransferFunctionTextureUpdater for texture updates.
*/
class TransferFunctionGui
{
public:
    /**
    * Constructor.
    * @param transferFunction Reference to the transfer function to edit.
    * @param guiUpdateFlags Reference to GUI update flags for change notification.
    */
    TransferFunctionGui(TransferFunction& transferFunction, GuiUpdateFlags& guiUpdateFlags);

    /**
    * Updates and renders the transfer function editor.
    * Should be called once per frame within an ImGui context.
    * @return void
    */
    void Update();

private:
    /**
    * Prepares cached values for interaction handling.
    */
    void PrepareInteraction();

    /**
    * Handles all user interactions (hover, click, drag, double-click).
    */
    void HandleInteraction();

    /**
    * Handles mouse hover over control points.
    */
    void HandleHover();

    /**
    * Handles double-click to add new control points.
    */
    void HandleDoubleClick();

    /**
    * Handles click to select control points or open color picker.
    */
    void HandleClick();

    /**
    * Handles dragging control points to modify value/opacity.
    */
    void HandleDrag();

    /**
    * Draws all visual elements of the transfer function editor.
    */
    void Draw();

    /**
    * Draws the background of the editor widget.
    */
    void DrawBackground(ImDrawList& drawList);

    /**
    * Draws grid lines for visual reference.
    */
    void DrawGrid(ImDrawList& drawList);

    /**
    * Draws the interpolated color gradient at the bottom.
    */
    void DrawColorGradient(ImDrawList& drawList);

    /**
    * Draws the opacity curve connecting control points.
    */
    void DrawOpacityCurve(ImDrawList& drawList);

    /**
    * Draws control point circles with visual feedback.
    */
    void DrawControlPoints(ImDrawList& drawList);

    /**
    * Draws the color picker popup for the selected control point.
    */
    void DrawColorPicker();

    /**
    * Sets the appropriate mouse cursor based on interaction state.
    */
    void SetMouseCursor();

    /**
    * Finds the nearest control point to the current mouse position.
    * @return Optional index of the nearest point, or std::nullopt if none are close enough.
    */
    std::optional<size_t> GetNearestPointIndex() const;

private:
    bool m_wasClicked; /**< Whether a click occurred in the previous frame. */
    size_t m_numActivePoints; /**< Number of active control points in the transfer function. */
    std::optional<size_t> m_draggedPointIndex; /**< Index of the control point being dragged, or std::nullopt. */
    std::optional<size_t> m_colorPickerPointIndex; /**< Index of the control point whose color is being edited, or std::nullopt. */
    std::optional<size_t> m_hoveredPointIndex; /**< Index of the control point being hovered over, or std::nullopt. */
    float m_interactiveAreaHeight; /**< Height in pixels of the interactive opacity curve area. */
    float m_gradientHeight; /**< Height in pixels of the color gradient bar. */
    ImVec2 m_plotSize; /**< Total size of the editor widget in pixels. */
    ImVec2 m_plotPos; /**< Screen position of the top-left corner of the widget. */
    ImVec2 m_mousePos; /**< Current mouse position in screen coordinates. */
    TransferFunction& m_transferFunction; /**< Reference to the transfer function being edited. */
    GuiUpdateFlags& m_guiUpdateFlags; /**< Reference to GUI update flags for change notification. */
};

#endif
