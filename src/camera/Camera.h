// Copyright https://learnopengl.com/

#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

struct CameraParameters;

class Camera
{
public:
    Camera(const CameraParameters& cameraParameters);

    float GetZoom() const;
    glm::vec3 GetPosition() const;
    glm::mat4 GetViewMatrix() const;

    void ProcessMouseScroll(float yoffset);
    void ProcessMouseMovement(float xoffset, float yoffset, bool invertY, float sensitivity);

private:
    float m_zoom;
    glm::vec3 m_position;
    glm::vec3 m_lookAt;
    glm::vec3 m_worldUp;
    glm::vec3 m_front;
    glm::vec3 m_right;
    glm::vec3 m_up;
};

#endif
