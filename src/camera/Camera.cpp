// Copyright https://learnopengl.com/

#include <camera/Camera.h>
#include <config/Config.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


Camera::Camera(const glm::vec3& position, const glm::vec3& lookAt, const glm::vec3& up)
    : m_zoom(Config::defaultCameraZoom)
    , m_position(position)
    , m_lookAt(lookAt)
    , m_front(glm::normalize(m_lookAt - m_position))
    , m_worldUp(up)
    , m_right(glm::normalize(glm::cross(m_front, m_worldUp)))
    , m_up(glm::normalize(glm::cross(m_right, m_front)))
{
}

float Camera::GetZoom() const
{
    return m_zoom;
}

glm::vec3 Camera::GetPosition() const
{
    return m_position;
}

glm::mat4 Camera::GetViewMatrix() const
{
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

void Camera::ProcessMouseScroll(float yoffset)
{
    m_zoom -= static_cast<float>(yoffset);
    if (m_zoom < 1.0f)
    {
        m_zoom = 1.0f;
    }
    if (m_zoom > Config::defaultCameraZoom)
    {
        m_zoom = Config::defaultCameraZoom;
    }
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool invertY, float sensitivity)
{
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    if (invertY)
    {
        yoffset = -yoffset;
    }

    // Calculate the vector from target to camera
    glm::vec3 toCamera = m_position - m_lookAt;
    float radius = glm::length(toCamera);

    // Horizontal rotation around world up axis
    glm::mat4 horizontalRotation = glm::rotate(glm::mat4(1.0f), -xoffset, m_worldUp);

    // Vertical rotation around right axis
    glm::mat4 verticalRotation = glm::rotate(glm::mat4(1.0f), -yoffset, m_right);

    // Apply rotations
    glm::vec4 rotatedPosition = horizontalRotation * verticalRotation * glm::vec4(toCamera, 1.0f);
    m_position = m_lookAt + glm::vec3(rotatedPosition);

    // Update camera vectors
    m_front = glm::normalize(m_lookAt - m_position);
    m_right = glm::normalize(glm::cross(m_front, m_worldUp));
    m_up = glm::normalize(glm::cross(m_right, m_front));
}

