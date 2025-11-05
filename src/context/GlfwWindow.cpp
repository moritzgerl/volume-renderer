#include "GlfwWindow.h"
#include "InitGlfw.h"
#include "InitGlad.h"
#include "InitGl.h"

#include <GLFW/glfw3.h>

namespace Context
{
    void GlfwWindow::WindowDeleterFunction(GLFWwindow* window)
    {
        if (window)
        {
            glfwDestroyWindow(window);
        }
    }

    GlfwWindow::GlfwWindow()
        : m_window(InitGlfw(), WindowDeleterFunction)
    {
        InitGlad();
        InitGl();
    }

    const WindowPtr& GlfwWindow::GetWindow() const
    {
        return m_window;
    }

    bool GlfwWindow::ShouldClose() const
    {
        return glfwWindowShouldClose(m_window.get());
    }

    void GlfwWindow::PostRender()
    {
        glfwSwapBuffers(m_window.get());
        glfwPollEvents();
    }

    void GlfwWindow::Shutdown()
    {
        glfwTerminate();
    }
}
