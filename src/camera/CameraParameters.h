#ifndef CAMERA_PARAMETERS_H
#define CAMERA_PARAMETERS_H

#include <glm/glm.hpp>

struct CameraParameters
{
    glm::vec3 position;
    glm::vec3 lookAt;
    glm::vec3 up;
    float zoom;
};

#endif
