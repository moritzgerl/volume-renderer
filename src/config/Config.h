#ifndef CONFIG_H
#define CONFIG_H

#include <lights/DirectionalLight.h>
#include <lights/PointLight.h>
#include <lights/MakeDefaultDirectionalLight.h>
#include <lights/MakeDefaultPointLights.h>
#include <transferfunction/MakeDefaultTransferFunction.h>

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
    const std::filesystem::path applicationStateIniFilePath = "./volume-renderer.ini";
    const std::filesystem::path datasetPath = "./datasets/knee.raw";
    const bool showLightSourceByDefault = false;
    const float defaultGuiWidthRatio = 0.3f;
    const float defaultTransferFunctionGuiHeightRatio = 0.3f;
    const unsigned int numPointLights = 2;
    const DirectionalLight defaultDirectionalLight = Factory::MakeDefaultDirectionalLight();
    const std::vector<PointLight> defaultPointLights = Factory::MakeDefaultPointLights(numPointLights);
    const TransferFunction defaultTransferFunction = Factory::MakeDefaultTransferFunction();
    const unsigned int defaultSsaoKernelSize = 64;
    const unsigned int defaultSsaoNoiseSize = 4;
    const float defaultSsaoRadius = 0.538f;
    const float defaultSsaoBias = 0.028f;
    const glm::vec3 defaultCameraPosition = glm::vec3(1.1f, 0.73f, 1.1f);
    const glm::vec3 defaultCameraLookAt = glm::vec3(0.0f, 0.0f, 0.0f);
    const glm::vec3 defaultCameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    const float defaultCameraZoom = 45.0f;
    const float trackballSensitivityMin = 0.0005f;
    const float trackballSensitivityMax = 0.005f;
    const float defaultTrackballSensitivity = 0.003f;
    const bool defaultTrackballInvertYAxis = true;
    const float defaultRaycastingDensityMultiplier = 20.0f;
}

#endif
