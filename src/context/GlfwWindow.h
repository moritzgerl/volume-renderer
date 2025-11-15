/**
* \file GlfwWindow.h
*
* \brief GLFW window wrapper for OpenGL context management.
*/

#ifndef GLFW_WINDOW_H
#define GLFW_WINDOW_H

#include <context/GlfwWindowTypes.h>

namespace Context
{
    /**
    * \class GlfwWindow
    *
    * \brief RAII wrapper for GLFW window creation and lifecycle management.
    *
    * Encapsulates a GLFW window with automatic initialization and cleanup.
    * Provides methods for checking window state, swapping buffers, and polling
    * events. Uses a custom deleter to ensure proper GLFW resource cleanup.
    *
    * The window is created in the constructor with the dimensions specified in
    * Config::windowWidth and Config::windowHeight. The OpenGL context is made
    * current automatically.
    *
    * @see GlfwWindowDeleter for custom resource cleanup.
    * @see InitGlfw for GLFW library initialization.
    * @see Config for window configuration constants.
    */
    class GlfwWindow
    {
    public:

        /**
        * Constructor.
        * Creates a GLFW window with OpenGL context and makes it current.
        */
        GlfwWindow();
        ~GlfwWindow() = default;

        GlfwWindow(const GlfwWindow&) = delete;
        GlfwWindow& operator=(const GlfwWindow&) = delete;
        GlfwWindow(GlfwWindow&&) = default;
        GlfwWindow& operator=(GlfwWindow&&) = default;

        /**
        * Gets the underlying GLFW window pointer.
        * @return Reference to the managed GLFW window pointer.
        */
        const WindowPtr& GetWindow() const;

        /**
        * Checks if the window should close.
        * @return True if the user requested window closure, false otherwise.
        */
        bool ShouldClose() const;

        /**
        * Performs post-render operations.
        * Swaps front and back buffers and polls for input events.
        * @return void
        */
        void PostRender();

        /**
        * Shuts down the GLFW window and terminates GLFW.
        * @return void
        */
        void Shutdown();

    private:
        WindowPtr m_window; /**< Managed GLFW window with custom deleter. */
    };
}

#endif
