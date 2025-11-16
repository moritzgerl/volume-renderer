/**
* \file GlfwWindowDeleter.h
*
* \brief Custom deleter for GLFW window smart pointers.
*/

#ifndef GLFW_WINDOW_DELETER_H
#define GLFW_WINDOW_DELETER_H

struct GLFWwindow;

namespace Context
{
    /**
    * \struct GlfwWindowDeleter
    *
    * \brief Custom deleter for std::unique_ptr managing GLFW windows.
    *
    * Provides proper cleanup for GLFW window resources when used with
    * std::unique_ptr. Calls glfwDestroyWindow to ensure the window is
    * properly destroyed when the unique_ptr goes out of scope.
    *
    * This enables RAII-style management of GLFW windows, ensuring that
    * resources are automatically cleaned up without manual calls to
    * glfwDestroyWindow.
    *
    * @see GlfwWindowTypes for the WindowPtr type alias.
    * @see GlfwWindow for GLFW window wrapper using this deleter.
    */
    struct GlfwWindowDeleter
    {
        /**
        * Destroys the GLFW window.
        * @param window Pointer to the GLFW window to destroy.
        */
        void operator()(GLFWwindow* window) const;
    };
}

#endif
