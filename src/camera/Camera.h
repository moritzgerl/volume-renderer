// Copyright https://learnopengl.com/

#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

const float ZOOM = 45.0f;

class Camera
{
public:
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));
    Camera(float posX, float posY, float posZ, float targetX, float targetY, float targetZ, float upX, float upY, float upZ);

    glm::mat4 GetViewMatrix() const;
    void ProcessMouseMovement(float xoffset, float yoffset);
    void ProcessMouseScroll(float yoffset);
    void PrintProperties();

    glm::vec3 GetPosition() const;
    float GetZoom() const;

private:
    void updateCameraVectors();

private:
    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;
    glm::vec3 m_worldUp;
    float m_zoom;
};

#endif
