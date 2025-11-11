#include <persistence/ParseGuiParameter.h>
#include <persistence/ParseValue.h>
#include <variant>

namespace
{
    unsigned int SanitizePointLightIndex(unsigned int elementIndex, Persistence::ApplicationStateIniFileSection section, const GuiParameters& guiParameters)
    {
        return section == Persistence::ApplicationStateIniFileSection::PointLight
            ? static_cast<unsigned int>(std::min(static_cast<size_t>(elementIndex), guiParameters.pointLights.size() - 1))
            : 0;
    }

    std::variant <Persistence::ParseValueResult<unsigned int>, Persistence::ParseValueResult<float> > ParseValueToVariant(
        Persistence::ApplicationStateIniFileKey key,
        std::string_view valueString)
    {
        using Key = Persistence::ApplicationStateIniFileKey;

        switch (key)
        {
        case Key::TrackballInvertYAxis:
        case Key::SsaoKernelSize:
        case Key::SsaoNoiseSize:
        case Key::SsaoEnable:
        case Key::ShowLightSources:
            return Persistence::ParseValue<unsigned int>(valueString);
        default:
            return Persistence::ParseValue<float>(valueString);
        }
    }
}

std::expected<void, Persistence::ApplicationStateIniFileLoadingError> Persistence::ParseGuiParameter(
    ApplicationStateIniFileSection section,
    ApplicationStateIniFileKey key,
    unsigned int elementIndex,
    std::string_view valueString,
    GuiParameters& guiParameters)
{
    auto parseValueResult = ParseValueToVariant(key, valueString);
    const unsigned int pointLightIndex = SanitizePointLightIndex(elementIndex, section, guiParameters);
    DirectionalLight& directionalLight = guiParameters.directionalLight;
    PointLight& pointLight = guiParameters.pointLights[pointLightIndex];

    return std::visit(
        [&]
        (const auto& result) -> std::expected<void, ApplicationStateIniFileLoadingError>
        {
            if (!result)
            {
                return std::unexpected(result.error());
            }

            const auto value = result.value();
            using Key = ApplicationStateIniFileKey;

            switch (key)
            {
            case Key::TrackballInvertYAxis:
                guiParameters.trackballInvertYAxis = static_cast<bool>(value);
                break;
            case Key::TrackballSensitivity:
                guiParameters.trackballSensitivity = static_cast<float>(value);
                break;
            case Key::SsaoKernelSize:
                guiParameters.ssaoKernelSize = static_cast<unsigned int>(value);
                break;
            case Key::SsaoNoiseSize:
                guiParameters.ssaoNoiseSize = static_cast<unsigned int>(value);
                break;
            case Key::SsaoRadius:
                guiParameters.ssaoRadius = static_cast<float>(value);
                break;
            case Key::SsaoBias:
                guiParameters.ssaoBias = static_cast<float>(value);
                break;
            case Key::SsaoEnable:
                guiParameters.enableSsao = static_cast<bool>(value);
                break;
            case Key::DirectionX:
                directionalLight.direction.x = static_cast<float>(value);
                break;
            case Key::DirectionY:
                directionalLight.direction.y = static_cast<float>(value);
                break;
            case Key::DirectionZ:
                directionalLight.direction.z = static_cast<float>(value);
                break;
            case Key::PositionX:
                pointLight.position.x = static_cast<float>(value);
                break;
            case Key::PositionY:
                pointLight.position.y = static_cast<float>(value);
                break;
            case Key::PositionZ:
                pointLight.position.z = static_cast<float>(value);
                break;
            // TODO use reflection?
            case Key::AmbientR:
                switch (section)
                {
                case ApplicationStateIniFileSection::DirectionalLight:
                    directionalLight.ambient.r = static_cast<float>(value);
                    break;
                case ApplicationStateIniFileSection::PointLight:
                    pointLight.ambient.r = static_cast<float>(value);
                    break;
                default:
                    break;
                }
                break;
            case Key::AmbientG:
                switch (section)
                {
                case ApplicationStateIniFileSection::DirectionalLight:
                    directionalLight.ambient.g = static_cast<float>(value);
                    break;
                case ApplicationStateIniFileSection::PointLight:
                    pointLight.ambient.g = static_cast<float>(value);
                    break;
                default:
                    break;
                }
                break;
            case Key::AmbientB:
                switch (section)
                {
                case ApplicationStateIniFileSection::DirectionalLight:
                    directionalLight.ambient.b = static_cast<float>(value);
                    break;
                case ApplicationStateIniFileSection::PointLight:
                    pointLight.ambient.b = static_cast<float>(value);
                    break;
                default:
                    break;
                }
                break;
            case Key::DiffuseR:
                switch (section)
                {
                case ApplicationStateIniFileSection::DirectionalLight:
                    directionalLight.diffuse.r = static_cast<float>(value);
                    break;
                case ApplicationStateIniFileSection::PointLight:
                    pointLight.diffuse.r = static_cast<float>(value);
                    break;
                default:
                    break;
                }
                break;
            case Key::DiffuseG:
                switch (section)
                {
                case ApplicationStateIniFileSection::DirectionalLight:
                    directionalLight.diffuse.g = static_cast<float>(value);
                    break;
                case ApplicationStateIniFileSection::PointLight:
                    pointLight.diffuse.g = static_cast<float>(value);
                    break;
                default:
                    break;
                }
                break;
            case Key::DiffuseB:
                switch (section)
                {
                case ApplicationStateIniFileSection::DirectionalLight:
                    directionalLight.diffuse.b = static_cast<float>(value);
                    break;
                case ApplicationStateIniFileSection::PointLight:
                    pointLight.diffuse.b = static_cast<float>(value);
                    break;
                default:
                    break;
                }
                break;
            case Key::SpecularR:
                switch (section)
                {
                case ApplicationStateIniFileSection::DirectionalLight:
                    directionalLight.specular.r = static_cast<float>(value);
                    break;
                case ApplicationStateIniFileSection::PointLight:
                    pointLight.specular.r = static_cast<float>(value);
                    break;
                default:
                    break;
                }
                break;
            case Key::SpecularG:
                switch (section)
                {
                case ApplicationStateIniFileSection::DirectionalLight:
                    directionalLight.specular.g = static_cast<float>(value);
                    break;
                case ApplicationStateIniFileSection::PointLight:
                    pointLight.specular.g = static_cast<float>(value);
                    break;
                default:
                    break;
                }
                break;
            case Key::SpecularB:
                switch (section)
                {
                case ApplicationStateIniFileSection::DirectionalLight:
                    directionalLight.specular.b = static_cast<float>(value);
                    break;
                case ApplicationStateIniFileSection::PointLight:
                    pointLight.specular.b = static_cast<float>(value);
                    break;
                default:
                    break;
                }
                break;
            case Key::Intensity:
                switch (section)
                {
                case ApplicationStateIniFileSection::DirectionalLight:
                    directionalLight.intensity = static_cast<float>(value);
                    break;
                case ApplicationStateIniFileSection::PointLight:
                    pointLight.intensity = static_cast<float>(value);
                    break;
                default:
                    break;
                }
                break;
            case Key::ShowLightSources:
                guiParameters.showLightSources = static_cast<bool>(value);
                break;
            case Key::DensityMultiplier:
                guiParameters.raycastingDensityMultiplier = static_cast<float>(value);
                break;
            default:
                break;
            }

            return {};
        },
        parseValueResult);
}
