#ifndef GUI_H
#define GUI_H

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <context/GlfwWindowTypes.h>

struct GuiParameters;
struct GuiUpdateFlags;

class Gui
{
public:
    Gui(const Context::WindowPtr& window, GuiParameters& guiParameters, GuiUpdateFlags& guiUpdateFlags);
    void Shutdown();
    void Draw();
    float GetGuiWidth() const;

private:
    const Context::WindowPtr& m_window;
    GuiParameters& m_guiParameters;
    GuiUpdateFlags& m_guiUpdateFlags;
    float m_guiWidth;
};

#endif
