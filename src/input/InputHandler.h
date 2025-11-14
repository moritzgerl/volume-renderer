/**
* \file InputHandler.h
*
* \brief Keyboard and mouse input handling for camera control and application state.
*/

#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <context/GlfwWindowTypes.h>

class Camera;
class VertexBuffer;
struct DisplayProperties;
struct GuiParameters;

/**
* \class InputHandler
*
* \brief Processes keyboard and mouse input via GLFW callbacks.
*
* Handles user input for camera control (mouse movement, scroll), application
* state toggling (GUI visibility, debug views), and window events (resize).
* Updates the Camera based on mouse movement and scroll, and modifies
* DisplayProperties based on keyboard input.
*
* GLFW callbacks are set up to forward events to the InputHandler instance
* stored in the window's user pointer.
*
* @see Camera for camera transformations.
* @see DisplayProperties for window state and GUI visibility.
* @see GuiParameters for trackball control settings.
* @see Factory::MakeInputHandler for construction with Storage references.
*/
class InputHandler
{
public:
    /**
    * Constructor.
    * @param window The GLFW window reference for setting up callbacks.
    * @param camera Reference to the camera to update based on input.
    * @param displayProperties Reference to display properties to modify based on input.
    * @param guiParameters Reference to GUI parameters for accessing trackball settings.
    */
    InputHandler(const Context::WindowPtr& window, Camera& camera, DisplayProperties& displayProperties, GuiParameters& guiParameters);

    /**
    * Updates input state and processes held keys.
    * Should be called once per frame.
    * @return void
    */
    void Update();

    unsigned int GetWindowWidth() const;
    unsigned int GetWindowHeight() const;

private:
    /**
    * Sets up GLFW callbacks for keyboard, mouse, and window events.
    */
    void InitGlfwCallbacks();

    /**
    * Processes keys that are held down (continuous actions).
    */
    void ProcessKeyHolds();

    /**
    * Processes key press/release events (discrete actions).
    */
    void ProcessKeyPresses(int key, int scancode, int action, int mods);

    /**
    * Processes mouse movement for camera rotation.
    */
    void ProcessMouseMove(double x, double y);

    /**
    * Processes mouse wheel scrolling for camera zoom.
    */
    void ProcessMouseWheel(double offsetX, double offsetY);

    /**
    * Processes window resize events.
    */
    void ProcessWindowResize(int width, int height);

private:
    unsigned int m_windowWidth; /**< Current window width in pixels. */
    unsigned int m_windowHeight; /**< Current window height in pixels. */
    float m_lastFrameTime; /**< Time of the last frame for delta time calculation. */
    float m_timeSinceLastFrame; /**< Time elapsed since the last frame. */
    bool m_isFirstMouseMove; /**< Whether this is the first mouse movement (to prevent jump). */
    float m_lastMousePositionX; /**< Last mouse X position for delta calculation. */
    float m_lastMousePositionY; /**< Last mouse Y position for delta calculation. */
    const Context::WindowPtr& m_window; /**< Reference to the GLFW window. */
    Camera& m_camera; /**< Reference to the camera to update. */
    DisplayProperties& m_displayProperties; /**< Reference to display properties to modify. */
    GuiParameters& m_guiParameters; /**< Reference to GUI parameters for trackball settings. */
};

#endif
