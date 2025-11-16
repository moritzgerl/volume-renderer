/**
* \file InitGlfw.h
*
* \brief Function for initializing the GLFW library.
*/

#ifndef INIT_GLFW_H
#define INIT_GLFW_H

struct GLFWwindow;

namespace Context
{
    /**
    * Initializes the GLFW library and creates a window with OpenGL context.
    *
    * Performs GLFW library initialization, sets error callbacks, and creates
    * a window with the configured dimensions and OpenGL context hints. This
    * function should be called before any other GLFW operations. The returned
    * window pointer is managed by the caller.
    *
    * @return Pointer to the created GLFW window, or nullptr on failure.
    *
    * @see GlfwWindow for RAII window wrapper.
    * @see InitGlad for loading OpenGL function pointers.
    * @see Config::windowWidth for window width configuration.
    * @see Config::windowHeight for window height configuration.
    */
    GLFWwindow* InitGlfw();
}

#endif
