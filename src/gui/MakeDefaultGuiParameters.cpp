#include <gui/MakeDefaultGuiParameters.h>
#include <config/Config.h>

GuiParameters Factory::MakeDefaultGuiParameters()
{
    GuiParameters guiParameters;
    guiParameters.transferFunction = Config::defaultTransferFunction;
    guiParameters.showLightSources = Config::showLightSourceByDefault;
    guiParameters.directionalLight = Config::defaultDirectionalLight;
    guiParameters.ssaoKernelSize = Config::defaultSsaoKernelSize;
    guiParameters.ssaoNoiseSize = Config::defaultSsaoNoiseSize;
    guiParameters.ssaoRadius = Config::defaultSsaoRadius;
    guiParameters.ssaoBias = Config::defaultSsaoBias;
    guiParameters.enableSsao = true;
    guiParameters.trackballInvertYAxis = Config::defaultTrackballInvertYAxis;
    guiParameters.trackballSensitivity = Config::defaultTrackballSensitivity;
    guiParameters.raycastingDensityMultiplier = Config::defaultRaycastingDensityMultiplier;

    for (unsigned int i = 0; i < Config::numPointLights; ++i)
    {
        guiParameters.pointLights.push_back(Config::defaultPointLights[i]);
    }

    return guiParameters;
}