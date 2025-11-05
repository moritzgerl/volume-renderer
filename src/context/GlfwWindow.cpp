#include <context/GlfwWindow.h>
#include <context/InitGlfw.h>
#include <context/InitGlad.h>
#include <context/InitGl.h>

#include <GLFW/glfw3.h>

namespace Context
{
    GlfwWindow::GlfwWindow()
        : m_window(InitGlfw())
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
