#ifndef GLFW_WINDOW_DELETER_H
#define GLFW_WINDOW_DELETER_H

struct GLFWwindow;

namespace Context
{
    struct GlfwWindowDeleter
    {
        void operator()(GLFWwindow* window) const;
    };
}

#endif
