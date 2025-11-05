#include <context/GlfwWindowDeleter.h>

#include <GLFW/glfw3.h>

namespace Context
{
    void GlfwWindowDeleter::operator()(GLFWwindow* window) const
    {
        if (window)
        {
            glfwDestroyWindow(window);
        }
    }
}
