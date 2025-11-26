/**
* \file Config.h
*
* \brief Configuration constants for the volume renderer.
*
* Central location for compile-time configuration constants including window dimensions,
* file paths, default lighting parameters, camera settings, SSAO parameters, and transfer
* function defaults. These constants are used throughout the application for initialization.
*
* @see Factory::MakeStorage for using configuration values during storage initialization.
* @see Camera for default camera parameters.
* @see GuiParameters for default GUI parameter values.
*/

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

/**
* \namespace Config
*
* \brief Configuration namespace containing compile-time constants.
*
* Provides centralized configuration for window settings, file paths, default lighting,
* camera parameters, SSAO settings, and other application-wide constants.
*/
namespace Config
{
    constexpr unsigned int windowWidth = 1920;
    constexpr unsigned int windowHeight = 1080;
    //constexpr unsigned int windowWidth = 3840;
    //constexpr unsigned int windowHeight = 2160;
    const std::filesystem::path applicationStateIniFilePath = "./volume-renderer.ini";
    const std::filesystem::path datasetPath = "./datasets/knee.raw";
    const std::filesystem::path shadersPath = "./shaders";
    constexpr bool showLightSourceByDefault = false;
    constexpr float defaultGuiWidthRatio = 0.3f;
    constexpr float defaultTransferFunctionGuiHeightRatio = 0.3f;
    constexpr unsigned int numPointLights = 2;
    const DirectionalLight defaultDirectionalLight = Factory::MakeDefaultDirectionalLight();
    const std::vector<PointLight> defaultPointLights = Factory::MakeDefaultPointLights(numPointLights);
    // move to its own header, use constexpr
    const TransferFunction defaultTransferFunction = Factory::MakeDefaultTransferFunction();
    constexpr unsigned int defaultSsaoKernelSize = 64;
    constexpr unsigned int defaultSsaoNoiseSize = 4;
    constexpr float defaultSsaoRadius = 0.538f;
    constexpr float defaultSsaoBias = 0.028f;
    constexpr glm::vec3 defaultCameraPosition = glm::vec3(1.1f, 0.73f, 1.1f);
    constexpr glm::vec3 defaultCameraLookAt = glm::vec3(0.0f, 0.0f, 0.0f);
    constexpr glm::vec3 defaultCameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    constexpr float defaultCameraZoom = 45.0f;
    constexpr float trackballSensitivityMin = 0.0005f;
    constexpr float trackballSensitivityMax = 0.005f;
    constexpr float defaultTrackballSensitivity = 0.003f;
    constexpr bool defaultTrackballInvertYAxis = true;
    constexpr float defaultRaycastingDensityMultiplier = 20.0f;
}

#endif
