#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <context/GlfwWindowTypes.h>

class Camera;
class VertexBuffer;
struct DisplayProperties;
struct GuiParameters;

class InputHandler
{
public:
    InputHandler(const Context::WindowPtr& window, Camera& camera, DisplayProperties& displayProperties, GuiParameters& guiParameters);
    void Update();
    unsigned int GetWindowWidth() const;
    unsigned int GetWindowHeight() const;

private:
    void InitGlfwCallbacks();
    void ProcessKeyHolds();
    void ProcessKeyPresses(int key, int scancode, int action, int mods);
    void ProcessMouseMove(double x, double y);
    void ProcessMouseWheel(double offsetX, double offsetY);
    void ProcessWindowResize(int width, int height);

private:
    unsigned int m_windowWidth;
    unsigned int m_windowHeight;
    float m_lastFrameTime;
    float m_timeSinceLastFrame;
    bool m_isFirstMouseMove;
    float m_lastMousePositionX;
    float m_lastMousePositionY;
    const Context::WindowPtr& m_window;
    Camera& m_camera;
    DisplayProperties& m_displayProperties;
    GuiParameters& m_guiParameters;
};

#endif
