#ifndef GLFW_WINDOW_H
#define GLFW_WINDOW_H

#include <context/GlfwWindowTypes.h>

namespace Context
{
    class GlfwWindow
    {
    public:

        GlfwWindow();
        ~GlfwWindow() = default;

        GlfwWindow(const GlfwWindow&) = delete;
        GlfwWindow& operator=(const GlfwWindow&) = delete;
        GlfwWindow(GlfwWindow&&) = default;
        GlfwWindow& operator=(GlfwWindow&&) = default;

        const WindowPtr& GetWindow() const;
        bool ShouldClose() const;
        void PostRender();
        void Shutdown();

    private:
        WindowPtr m_window;
    };
}

#endif
