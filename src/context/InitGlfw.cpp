#include <context/InitGlfw.h>
#include <config/Config.h>
#include <GLFW/glfw3.h>
#include <iostream>

// TODO use unique_ptr for window
GLFWwindow* Context::InitGlfw()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(Config::windowWidth, Config::windowHeight, "Volume Renderer", nullptr, nullptr);

    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);

    return window;
}
