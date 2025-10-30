#ifndef GUI_H
#define GUI_H

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

struct GuiParameters;
struct GuiUpdateFlags;

class Gui
{
public:
    Gui(GLFWwindow* window, GuiParameters& guiParameters, GuiUpdateFlags& guiUpdateFlags);
    void Shutdown();
    void Draw();

private:
    GLFWwindow* m_window;
    GuiParameters& m_guiParameters;
    GuiUpdateFlags& m_guiUpdateFlags;
};

#endif
