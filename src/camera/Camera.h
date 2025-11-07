// Copyright https://learnopengl.com/

#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Camera
{
public:
    Camera(float posX, float posY, float posZ, float targetX, float targetY, float targetZ, float upX, float upY, float upZ);

    float GetZoom() const;
    glm::vec3 GetPosition() const;
    glm::mat4 GetViewMatrix() const;

    void ProcessMouseScroll(float yoffset);
    void ProcessMouseMovement(float xoffset, float yoffset);

private:
    float m_zoom;
    glm::vec3 m_position;
    glm::vec3 m_target;
    glm::vec3 m_worldUp;  // Must be before m_front, m_right, m_up since they depend on it
    glm::vec3 m_front;
    glm::vec3 m_right;
    glm::vec3 m_up;
};

#endif
