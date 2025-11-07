// Copyright https://learnopengl.com/

#include <camera/Camera.h>
#include <config/Config.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <iomanip>

Camera::Camera(float posX, float posY, float posZ, float targetX, float targetY, float targetZ, float upX, float upY, float upZ)
    : m_zoom(Config::defaultZoom)
{
    m_position = glm::vec3(posX, posY, posZ);
    m_worldUp = glm::vec3(upX, upY, upZ);
    glm::vec3 target = glm::vec3(targetX, targetY, targetZ);
    m_front = glm::normalize(target - m_position);
    updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() const
{
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset)
{
    // TODO: Implement trackball rotation
}

void Camera::ProcessMouseScroll(float yoffset)
{
    m_zoom -= static_cast<float>(yoffset);
    if (m_zoom < 1.0f)
    {
        m_zoom = 1.0f;
    }
    if (m_zoom > Config::defaultZoom)
    {
        m_zoom = Config::defaultZoom;
    }
}

void Camera::PrintProperties()
{
    std::cout << std::fixed << std::setw(10) << std::setprecision(8) <<
        m_position.x << "f, " << m_position.y << "f, " << m_position.z << "f" << std::endl;
}

glm::vec3 Camera::GetPosition() const
{
    return m_position;
}

float Camera::GetZoom() const
{
    return m_zoom;
}

void Camera::updateCameraVectors()
{
    m_right = glm::normalize(glm::cross(m_front, m_worldUp));
    m_up = glm::normalize(glm::cross(m_right, m_front));
}
