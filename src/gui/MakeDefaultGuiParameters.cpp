#include <gui/MakeDefaultGuiParameters.h>
#include <config/Config.h>

GuiParameters Factory::MakeDefaultGuiParameters()
{
    return GuiParameters {
        Config::defaultTransferFunction,
        Config::showLightSourceByDefault,
        Config::defaultDirectionalLight,
        Config::defaultPointLights,
        Config::defaultSsaoKernelSize,
        Config::defaultSsaoNoiseSize,
        Config::defaultSsaoRadius,
        Config::defaultSsaoBias,
        true,
        Config::defaultTrackballInvertYAxis,
        Config::defaultTrackballSensitivity,
        Config::defaultRaycastingDensityMultiplier
    };
}