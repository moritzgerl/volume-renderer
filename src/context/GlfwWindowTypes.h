#ifndef GLFW_WINDOW_TYPES_H
#define GLFW_WINDOW_TYPES_H

#include <memory>

struct GLFWwindow;

namespace Context
{
    using WindowDeleter = void(*)(GLFWwindow*);
    using WindowPtr = std::unique_ptr<GLFWwindow, WindowDeleter>;
}

#endif
