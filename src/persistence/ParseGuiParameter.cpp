#include <persistence/ParseGuiParameter.h>
#include <persistence/ParseValue.h>
#include <variant>

namespace
{
    unsigned int SanitizePointLightIndex(unsigned int elementIndex, Data::ApplicationStateIniFileSection section, const GuiParameters& guiParameters)
    {
        return section == Data::ApplicationStateIniFileSection::PointLight
            ? std::max(static_cast<size_t>(elementIndex), guiParameters.pointLights.size() - 1)
            : 0;
    }

    std::variant <Parsing::ParseValueResult<unsigned int>, Parsing::ParseValueResult<float> > ParseValueToVariant(
        Data::ApplicationStateIniFileKey key,
        std::string_view valueString)
    {
        using Key = Data::ApplicationStateIniFileKey;

        switch (key)
        {
        case Key::TrackballInvertYAxis:
        case Key::SsaoKernelSize:
        case Key::SsaoNoiseSize:
        case Key::SsaoEnable:
        case Key::ShowLightSources:
            return Parsing::ParseValue<unsigned int>(valueString);
        default:
            return Parsing::ParseValue<float>(valueString);
        }
    }
}

bool Parsing::ParseGuiParameter(
    Data::ApplicationStateIniFileSection section,
    Data::ApplicationStateIniFileKey key,
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
        (const auto& result) -> bool
        {
            if (!result)
            {
                return false;
            }

            const auto value = result.value();
            using Key = Data::ApplicationStateIniFileKey;

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
                case Data::ApplicationStateIniFileSection::DirectionalLight:
                    directionalLight.ambient.r = static_cast<float>(value);
                    break;
                case Data::ApplicationStateIniFileSection::PointLight:
                    pointLight.ambient.r = static_cast<float>(value);
                    break;
                default:
                    break;
                }
                break;
            case Key::AmbientG:
                switch (section)
                {
                case Data::ApplicationStateIniFileSection::DirectionalLight:
                    directionalLight.ambient.g = static_cast<float>(value);
                    break;
                case Data::ApplicationStateIniFileSection::PointLight:
                    pointLight.ambient.g = static_cast<float>(value);
                    break;
                default:
                    break;
                }
                break;
            case Key::AmbientB:
                switch (section)
                {
                case Data::ApplicationStateIniFileSection::DirectionalLight:
                    directionalLight.ambient.b = static_cast<float>(value);
                    break;
                case Data::ApplicationStateIniFileSection::PointLight:
                    pointLight.ambient.b = static_cast<float>(value);
                    break;
                default:
                    break;
                }
                break;
            case Key::DiffuseR:
                switch (section)
                {
                case Data::ApplicationStateIniFileSection::DirectionalLight:
                    directionalLight.diffuse.r = static_cast<float>(value);
                    break;
                case Data::ApplicationStateIniFileSection::PointLight:
                    pointLight.diffuse.r = static_cast<float>(value);
                    break;
                default:
                    break;
                }
                break;
            case Key::DiffuseG:
                switch (section)
                {
                case Data::ApplicationStateIniFileSection::DirectionalLight:
                    directionalLight.diffuse.g = static_cast<float>(value);
                    break;
                case Data::ApplicationStateIniFileSection::PointLight:
                    pointLight.diffuse.g = static_cast<float>(value);
                    break;
                default:
                    break;
                }
                break;
            case Key::DiffuseB:
                switch (section)
                {
                case Data::ApplicationStateIniFileSection::DirectionalLight:
                    directionalLight.diffuse.b = static_cast<float>(value);
                    break;
                case Data::ApplicationStateIniFileSection::PointLight:
                    pointLight.diffuse.b = static_cast<float>(value);
                    break;
                default:
                    break;
                }
                break;
            case Key::SpecularR:
                switch (section)
                {
                case Data::ApplicationStateIniFileSection::DirectionalLight:
                    directionalLight.specular.r = static_cast<float>(value);
                    break;
                case Data::ApplicationStateIniFileSection::PointLight:
                    pointLight.specular.r = static_cast<float>(value);
                    break;
                default:
                    break;
                }
                break;
            case Key::SpecularG:
                switch (section)
                {
                case Data::ApplicationStateIniFileSection::DirectionalLight:
                    directionalLight.specular.g = static_cast<float>(value);
                    break;
                case Data::ApplicationStateIniFileSection::PointLight:
                    pointLight.specular.g = static_cast<float>(value);
                    break;
                default:
                    break;
                }
                break;
            case Key::SpecularB:
                switch (section)
                {
                case Data::ApplicationStateIniFileSection::DirectionalLight:
                    directionalLight.specular.b = static_cast<float>(value);
                    break;
                case Data::ApplicationStateIniFileSection::PointLight:
                    pointLight.specular.b = static_cast<float>(value);
                    break;
                default:
                    break;
                }
                break;
            case Key::Intensity:
                switch (section)
                {
                case Data::ApplicationStateIniFileSection::DirectionalLight:
                    directionalLight.intensity = static_cast<float>(value);
                    break;
                case Data::ApplicationStateIniFileSection::PointLight:
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

            return true;
        },
        parseValueResult);
}
