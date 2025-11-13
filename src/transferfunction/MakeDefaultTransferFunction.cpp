#include <transferfunction/MakeDefaultTransferFunction.h>

TransferFunction Factory::MakeDefaultTransferFunction()
{
    TransferFunction transferFunction;
    transferFunction.SetNumActivePoints(3);

    // First control point at 0.0
    transferFunction[0].value = 0.0f;
    transferFunction[0].color = glm::vec3(0.0f, 0.0f, 0.0f);
    transferFunction[0].opacity = 0.0f;

    // Second control point at 0.5
    transferFunction[1].value = 0.5f;
    transferFunction[1].color = glm::vec3(1.0f, 0.5f, 0.0f);
    transferFunction[1].opacity = 0.5f;

    // Third control point at 1.0
    transferFunction[2].value = 1.0f;
    transferFunction[2].color = glm::vec3(1.0f, 1.0f, 1.0f);
    transferFunction[2].opacity = 1.0f;

    return transferFunction;
}
