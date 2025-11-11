#include <gui/MakeDefaultTransferFunction.h>

TransferFunction MakeDefaultTransferFunction()
{
    TransferFunction tf;
    tf.SetNumActivePoints(3);

    // First control point at 0.0
    tf[0].value = 0.0f;
    tf[0].color = glm::vec3(0.0f, 0.0f, 0.0f);
    tf[0].opacity = 0.0f;

    // Second control point at 0.5
    tf[1].value = 0.5f;
    tf[1].color = glm::vec3(1.0f, 0.5f, 0.0f);
    tf[1].opacity = 0.5f;

    // Third control point at 1.0
    tf[2].value = 1.0f;
    tf[2].color = glm::vec3(1.0f, 1.0f, 1.0f);
    tf[2].opacity = 1.0f;

    return tf;
}
