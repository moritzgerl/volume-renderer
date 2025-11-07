// Copyright https://learnopengl.com/

#include <camera/Camera.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <iomanip>

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up)
    : Zoom(ZOOM)
{
    Position = position;
    WorldUp = up;
    Front = glm::normalize(target - position);
    updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float targetX, float targetY, float targetZ, float upX, float upY, float upZ)
    : Zoom(ZOOM)
{
    Position = glm::vec3(posX, posY, posZ);
    WorldUp = glm::vec3(upX, upY, upZ);
    glm::vec3 target = glm::vec3(targetX, targetY, targetZ);
    Front = glm::normalize(target - Position);
    updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() const
{
    return glm::lookAt(Position, Position + Front, Up);
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset)
{
    // TODO: Implement trackball rotation
}

void Camera::ProcessMouseScroll(float yoffset)
{
    Zoom -= static_cast<float>(yoffset);
    if (Zoom < 1.0f)
    {
        Zoom = 1.0f;
    }
    if (Zoom > 45.0f)
    {
        Zoom = 45.0f;
    }
}

void Camera::PrintProperties()
{
    std::cout << std::fixed << std::setw(10) << std::setprecision(8) <<
        Position.x << "f, " << Position.y << "f, " << Position.z << "f" << std::endl;
}

void Camera::updateCameraVectors()
{
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
}
