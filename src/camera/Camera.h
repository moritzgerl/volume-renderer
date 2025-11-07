// Copyright https://learnopengl.com/

#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

const float ZOOM = 45.0f;

class Camera
{
public:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    float Zoom;

    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));
    Camera(float posX, float posY, float posZ, float targetX, float targetY, float targetZ, float upX, float upY, float upZ);

    glm::mat4 GetViewMatrix() const;
    void ProcessMouseMovement(float xoffset, float yoffset);
    void ProcessMouseScroll(float yoffset);
    void PrintProperties();

private:
    void updateCameraVectors();
};

#endif
