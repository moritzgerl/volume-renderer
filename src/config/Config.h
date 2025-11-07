#ifndef CONFIG_H
#define CONFIG_H

#include <gui/MakeDefaultTransferFunction.h>
#include <lights/DirectionalLight.h>
#include <lights/PointLight.h>
#include <lights/MakeDefaultDirectionalLight.h>
#include <lights/MakeDefaultPointLights.h>

#include <glm/glm.hpp>

#include <filesystem>
#include <string>
#include <vector>

namespace Config
{
    const unsigned int windowWidth = 1920;
    const unsigned int windowHeight = 1080;
    //const unsigned int windowWidth = 3840;
    //const unsigned int windowHeight = 2160;
    const std::filesystem::path datasetPath = "./datasets/knee.raw";
    const bool showGuiByDefault = true;
    const bool showLightSourceByDefault = false;
    const unsigned int numPointLights = 2;
    const DirectionalLight defaultDirectionalLight = MakeDefaultDirectionalLight();
    const std::vector<PointLight> defaultPointLights = MakeDefaultPointLights(numPointLights);
    const unsigned int defaultSsaoKernelSize = 64;
    const unsigned int defaultSsaoNoiseSize = 4;
    const float defaultSsaoRadius = 0.538f;
    const float defaultSsaoBias = 0.028f;
    const float defaultZoom = 45.0f;
    const float trackballSensitivity = 0.005f;
    const TransferFunction defaultTransferFunction = MakeDefaultTransferFunction();
}

#endif
