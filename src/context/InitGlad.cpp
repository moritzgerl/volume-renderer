#include <context/InitGlad.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void Context::InitGlad()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
}
