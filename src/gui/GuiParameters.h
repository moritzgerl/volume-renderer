#ifndef GUI_PARAMETERS_H
#define GUI_PARAMETERS_H

#include <lights/DirectionalLight.h>
#include <lights/PointLight.h>
#include <transferfunction/TransferFunction.h>

#include <vector>

struct GuiParameters
{
    TransferFunction transferFunction;
    bool showLightSources;
    DirectionalLight directionalLight;
    std::vector<PointLight> pointLights;
    unsigned int ssaoKernelSize;
    unsigned int ssaoNoiseSize;
    float ssaoRadius;
    float ssaoBias;
    bool enableSsao;
    bool trackballInvertYAxis;
    float trackballSensitivity;
    float raycastingDensityMultiplier;
};

#endif
