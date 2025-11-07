#ifndef TRANSFER_FUNCTION_CONTROL_POINT_H
#define TRANSFER_FUNCTION_CONTROL_POINT_H

#include <glm/glm.hpp>

struct TransferFunctionControlPoint
{
    float value;        // Scalar value [0, 1]
    glm::vec3 color;    // RGB color
    float opacity;      // Alpha/opacity [0, 1]
};

#endif
