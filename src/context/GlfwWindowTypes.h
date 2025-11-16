/**
* \file GlfwWindowTypes.h
*
* \brief Type aliases for GLFW window management.
*/

#ifndef GLFW_WINDOW_TYPES_H
#define GLFW_WINDOW_TYPES_H

#include <context/GlfwWindowDeleter.h>

#include <memory>

namespace Context
{
    /**
    * \typedef WindowPtr
    *
    * \brief Smart pointer type for GLFW window management.
    *
    * Type alias for std::unique_ptr with a custom deleter that properly
    * destroys GLFW windows. This provides automatic resource management
    * for GLFW windows following RAII principles.
    *
    * The custom deleter ensures glfwDestroyWindow is called when the
    * unique_ptr goes out of scope or is reset.
    *
    * @see GlfwWindowDeleter for the custom deleter implementation.
    * @see GlfwWindow for the window wrapper class using this type.
    */
    using WindowPtr = std::unique_ptr<GLFWwindow, GlfwWindowDeleter>;
}

#endif
