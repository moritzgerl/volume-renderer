/**
* \file Gui.h
*
* \brief ImGui-based graphical user interface for runtime parameter adjustment.
*/

#ifndef GUI_H
#define GUI_H

#include <gui/TransferFunctionGui.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <context/GlfwWindowTypes.h>

struct GuiParameters;
struct GuiUpdateFlags;

/**
* \class Gui
*
* \brief Manages the ImGui interface for tweaking rendering parameters.
*
* Provides interactive controls for adjusting lighting parameters, SSAO settings,
* camera controls, and the transfer function. Updates GuiParameters which drive
* shader uniforms, and sets GuiUpdateFlags to signal when expensive resources
* need regeneration (e.g., SSAO noise texture, transfer function texture).
*
* The GUI is organized into collapsing sections for different parameter categories.
* Also includes a transfer function editor for interactive control point manipulation.
*
* @see GuiParameters for the parameter structure that stores all GUI values.
* @see GuiUpdateFlags for signaling when resources need updates.
* @see TransferFunctionGui for the interactive transfer function editor.
* @see Factory::MakeGui for GUI construction.
*/
class Gui
{
public:
    /**
    * Constructor.
    * @param window The GLFW window reference for ImGui initialization.
    * @param guiParameters Reference to GUI parameters that will be modified by the GUI.
    * @param guiUpdateFlags Reference to update flags that signal when resources need regeneration.
    */
    Gui(const Context::WindowPtr& window, GuiParameters& guiParameters, GuiUpdateFlags& guiUpdateFlags);

    /**
    * Shuts down ImGui and cleans up resources.
    * @return void
    */
    void Shutdown();

    /**
    * Renders the GUI and processes user interactions.
    * @return void
    */
    void Draw();

    float GetGuiWidth() const;

private:
    const Context::WindowPtr& m_window; /**< The GLFW window for ImGui rendering. */
    GuiParameters& m_guiParameters; /**< Reference to GUI parameters modified by the interface. */
    GuiUpdateFlags& m_guiUpdateFlags; /**< Reference to flags indicating when resources need updates. */
    float m_guiWidth; /**< Current width of the GUI panel in pixels. */
    float m_transferFunctionHeight; /**< Current height of the transfer function editor in pixels. */
    TransferFunctionGui m_transferFunctionGui; /**< Transfer function editor widget. */
};

#endif
