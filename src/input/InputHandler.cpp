#include <input/InputHandler.h>
#include <camera/Camera.h>
#include <config/Config.h>
#include <input/DisplayProperties.h>
#include <storage/Storage.h>
#include <GLFW/glfw3.h>

InputHandler::InputHandler(const Context::WindowPtr& window, Camera& camera, DisplayProperties& displayProperties)
    : m_windowWidth(Config::windowWidth)
    , m_windowHeight(Config::windowHeight)
    , m_lastFrameTime(0.0f)
    , m_timeSinceLastFrame(0.0f)
    , m_isFirstMouseMove(true)
    , m_lastMousePositionX(Config::windowWidth / 2.0f)
    , m_lastMousePositionY(Config::windowHeight / 2.0f)
    , m_window(window)
    , m_camera(camera)
    , m_displayProperties(displayProperties)
{
    InitGlfwCallbacks();
}

void InputHandler::InitGlfwCallbacks()
{
    glfwSetWindowUserPointer(m_window.get(), static_cast<void*>(this));

    glfwSetKeyCallback(m_window.get(), [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        auto self = static_cast<InputHandler*>(glfwGetWindowUserPointer(window));
        self->ProcessKeyPresses(key, scancode, action, mods);
    });

    glfwSetFramebufferSizeCallback(m_window.get(), [](GLFWwindow* window, int width, int height)
    {
        auto self = static_cast<InputHandler*>(glfwGetWindowUserPointer(window));
        self->ProcessWindowResize(width, height);
    });

    glfwSetCursorPosCallback(m_window.get(), [](GLFWwindow* window, double x, double y)
    {
        auto self = static_cast<InputHandler*>(glfwGetWindowUserPointer(window));
        self->ProcessMouseMove(x, y);
    });

    glfwSetScrollCallback(m_window.get(), [](GLFWwindow* window, double offsetX, double offsetY)
    {
        auto self = static_cast<InputHandler*>(glfwGetWindowUserPointer(window));
        self->ProcessMouseWheel(offsetX, offsetY);
    });
}

void InputHandler::Update()
{
    if (m_window.get() == nullptr)
    {
        return;
    }

    float currentFrameTime = static_cast<float>(glfwGetTime());
    m_timeSinceLastFrame = currentFrameTime - m_lastFrameTime;
    m_lastFrameTime = currentFrameTime;

    ProcessKeyHolds();
}

unsigned int InputHandler::GetWindowWidth() const
{
    return m_windowWidth;
}

unsigned int InputHandler::GetWindowHeight() const
{
    return m_windowHeight;
}

void InputHandler::ProcessKeyHolds()
{
    if (glfwGetKey(m_window.get(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(m_window.get(), true);
    }
}

void InputHandler::ProcessKeyPresses(int key, int scancode, int action, int mods)
{
    if (glfwGetKey(m_window.get(), GLFW_KEY_G) == GLFW_PRESS)
    {
        m_displayProperties.showGui= !m_displayProperties.showGui;
    }

    if (glfwGetKey(m_window.get(), GLFW_KEY_F6) == GLFW_PRESS)
    {
        m_displayProperties.showSsaoMap = !m_displayProperties.showSsaoMap;
    }
}

void InputHandler::ProcessMouseMove(double x, double y)
{
    float positionX = static_cast<float>(x);
    float positionY = static_cast<float>(y);

    if (m_isFirstMouseMove)
    {
        m_lastMousePositionX = positionX;
        m_lastMousePositionY = positionY;
        m_isFirstMouseMove = false;
    }

    float offsetX = positionX - m_lastMousePositionX;
    float offsetY = m_lastMousePositionY - positionY;

    m_lastMousePositionX = positionX;
    m_lastMousePositionY = positionY;

    if (glfwGetMouseButton(m_window.get(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        m_camera.ProcessMouseMovement(offsetX, offsetY);
    }
}

void InputHandler::ProcessMouseWheel(double offsetX, double offsetY)
{
    m_camera.ProcessMouseScroll(static_cast<float>(offsetY));
}

void InputHandler::ProcessWindowResize(int width, int height)
{
    glViewport(0, 0, width, height);
    m_windowWidth = width;
    m_windowHeight = height;
}
