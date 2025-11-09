#include <gui/MakeGuiParameters.h>
#include <config/Config.h>
#include <data/SaveState.h>

namespace
{
    bool IsTransferFunctionValid(const TransferFunction& transferFunction)
    {
        if (transferFunction.numActivePoints == 0)
        {
            return false;
        }

        if (transferFunction.numActivePoints > TransferFunction::maxControlPoints)
        {
            return false;
        }

        // TODO make nice
        // Check that all active points have valid values in [0, 1]
        for (size_t i = 0; i < transferFunction.numActivePoints; ++i)
        {
            const auto& point = transferFunction.controlPoints[i];
            if (point.value < 0.0f || point.value > 1.0f)
            {
                return false;
            }
            if (point.opacity < 0.0f || point.opacity > 1.0f)
            {
                return false;
            }
            // Color components should be in [0, 1] range
            if (point.color.r < 0.0f || point.color.r > 1.0f ||
                point.color.g < 0.0f || point.color.g > 1.0f ||
                point.color.b < 0.0f || point.color.b > 1.0f)
            {
                return false;
            }
        }

        return true;
    }
} // anonymous namespace

GuiParameters Factory::MakeGuiParameters(const std::optional<Data::SaveState>& saveState)
{
    GuiParameters guiParameters;
    guiParameters.showLightSources = Config::showLightSourceByDefault;
    guiParameters.directionalLight = Config::defaultDirectionalLight;
    guiParameters.ssaoKernelSize = Config::defaultSsaoKernelSize;
    guiParameters.ssaoNoiseSize = Config::defaultSsaoNoiseSize;
    guiParameters.ssaoRadius = Config::defaultSsaoRadius;
    guiParameters.ssaoBias = Config::defaultSsaoBias;
    guiParameters.enableSsao = true;
    guiParameters.trackballInvertYAxis = Config::defaultTrackballInvertYAxis;
    guiParameters.trackballSensitivity = Config::defaultTrackballSensitivity;

    // Use loaded transfer function if valid, otherwise fall back to default
    if (saveState.has_value() && IsTransferFunctionValid(saveState->transferFunction))
    {
        guiParameters.transferFunction = saveState->transferFunction;
    }
    else
    {
        guiParameters.transferFunction = Config::defaultTransferFunction;
    }

    guiParameters.raycastingDensityMultiplier = Config::defaultRaycastingDensityMultiplier;

    for (unsigned int i = 0; i < Config::numPointLights; ++i)
    {
        guiParameters.pointLights.push_back(Config::defaultPointLights[i]);
    }

    return guiParameters;
}