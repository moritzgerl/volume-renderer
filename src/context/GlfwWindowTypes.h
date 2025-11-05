#ifndef GLFW_WINDOW_TYPES_H
#define GLFW_WINDOW_TYPES_H

#include <context/GlfwWindowDeleter.h>

#include <memory>

namespace Context
{
    using WindowPtr = std::unique_ptr<GLFWwindow, GlfwWindowDeleter>;
}

#endif
