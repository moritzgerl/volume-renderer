#include <gui/MakeDefaultTransferFunction.h>

TransferFunction MakeDefaultTransferFunction()
{
    TransferFunction tf;
    tf.numActivePoints = 3;

    // First control point at 0.0
    tf.controlPoints[0].value = 0.0f;
    tf.controlPoints[0].color = glm::vec3(0.0f, 0.0f, 0.0f);
    tf.controlPoints[0].opacity = 0.0f;

    // Second control point at 0.5
    tf.controlPoints[1].value = 0.5f;
    tf.controlPoints[1].color = glm::vec3(1.0f, 0.5f, 0.0f);
    tf.controlPoints[1].opacity = 0.5f;

    // Third control point at 1.0
    tf.controlPoints[2].value = 1.0f;
    tf.controlPoints[2].color = glm::vec3(1.0f, 1.0f, 1.0f);
    tf.controlPoints[2].opacity = 1.0f;

    return tf;
}
