#ifndef GUI_PARAMETERS_H
#define GUI_PARAMETERS_H

#include <gui/TransferFunction.h>
#include <lights/DirectionalLight.h>
#include <lights/PointLight.h>

#include <vector>

struct GuiParameters
{
    bool showLightSources;
    DirectionalLight directionalLight;
    std::vector<PointLight> pointLights;
    unsigned int ssaoKernelSize;
    unsigned int ssaoNoiseSize;
    float ssaoRadius;
    float ssaoBias;
    bool enableSsao;
    TransferFunction transferFunction;
    float raycastingDensityMultiplier;
};

#endif
