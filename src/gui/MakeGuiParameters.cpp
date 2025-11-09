#include <gui/MakeGuiParameters.h>
#include <config/Config.h>

GuiParameters Factory::MakeGuiParameters()
{
    GuiParameters guiParameters;
    guiParameters.showLightSources = Config::showLightSourceByDefault;
    guiParameters.directionalLight = Config::defaultDirectionalLight;
    guiParameters.ssaoKernelSize = Config::defaultSsaoKernelSize;
    guiParameters.ssaoNoiseSize = Config::defaultSsaoNoiseSize;
    guiParameters.ssaoRadius = Config::defaultSsaoRadius;
    guiParameters.ssaoBias = Config::defaultSsaoBias;
    guiParameters.enableSsao = true;
    guiParameters.transferFunction = Config::defaultTransferFunction;
    guiParameters.raycastingDensityMultiplier = Config::defaultRaycastingDensityMultiplier;

    for (unsigned int i = 0; i < Config::numPointLights; ++i)
    {
        guiParameters.pointLights.push_back(Config::defaultPointLights[i]);
    }

    return guiParameters;
}