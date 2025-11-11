#include <persistence/GetApplicationStateIniFileKey.h>
#include <algorithm>
#include <array>

namespace
{
    struct ApplicationStateIniFileKeyMapping
    {
        std::string_view key;
        Persistence::ApplicationStateIniFileKey value;
    };

    constexpr std::array<ApplicationStateIniFileKeyMapping, 31> applicationStateIniFileKeyLookup =
    {{  
        {"PositionX", Persistence::ApplicationStateIniFileKey::PositionX},
        {"PositionY", Persistence::ApplicationStateIniFileKey::PositionY},
        {"PositionZ", Persistence::ApplicationStateIniFileKey::PositionZ},
        {"Zoom", Persistence::ApplicationStateIniFileKey::Zoom},
        {"Value", Persistence::ApplicationStateIniFileKey::Value},
        {"ColorR", Persistence::ApplicationStateIniFileKey::ColorR},
        {"ColorG", Persistence::ApplicationStateIniFileKey::ColorG},
        {"ColorB", Persistence::ApplicationStateIniFileKey::ColorB},
        {"Opacity", Persistence::ApplicationStateIniFileKey::Opacity},
        {"TrackballInvertYAxis", Persistence::ApplicationStateIniFileKey::TrackballInvertYAxis},
        {"TrackballSensitivity", Persistence::ApplicationStateIniFileKey::TrackballSensitivity},
        {"SsaoKernelSize", Persistence::ApplicationStateIniFileKey::SsaoKernelSize},
        {"SsaoNoiseSize", Persistence::ApplicationStateIniFileKey::SsaoNoiseSize},
        {"SsaoRadius", Persistence::ApplicationStateIniFileKey::SsaoRadius},
        {"SsaoBias", Persistence::ApplicationStateIniFileKey::SsaoBias},
        {"SsaoEnable", Persistence::ApplicationStateIniFileKey::SsaoEnable},
        {"DirectionX", Persistence::ApplicationStateIniFileKey::DirectionX},
        {"DirectionY", Persistence::ApplicationStateIniFileKey::DirectionY},
        {"DirectionZ", Persistence::ApplicationStateIniFileKey::DirectionZ},
        {"AmbientR", Persistence::ApplicationStateIniFileKey::AmbientR},
        {"AmbientG", Persistence::ApplicationStateIniFileKey::AmbientG},
        {"AmbientB", Persistence::ApplicationStateIniFileKey::AmbientB},
        {"DiffuseR", Persistence::ApplicationStateIniFileKey::DiffuseR},
        {"DiffuseG", Persistence::ApplicationStateIniFileKey::DiffuseG},
        {"DiffuseB", Persistence::ApplicationStateIniFileKey::DiffuseB},
        {"SpecularR", Persistence::ApplicationStateIniFileKey::SpecularR},
        {"SpecularG", Persistence::ApplicationStateIniFileKey::SpecularG},
        {"SpecularB", Persistence::ApplicationStateIniFileKey::SpecularB},
        {"Intensity", Persistence::ApplicationStateIniFileKey::Intensity},
        {"ShowLightSources", Persistence::ApplicationStateIniFileKey::ShowLightSources},
        {"DensityMultiplier", Persistence::ApplicationStateIniFileKey::DensityMultiplier}
    }};
}

Persistence::ApplicationStateIniFileKey Persistence::GetApplicationStateIniFileKey(std::string_view key)
{
    auto it = std::find_if(applicationStateIniFileKeyLookup.begin(), applicationStateIniFileKeyLookup.end(),
        [key](const ApplicationStateIniFileKeyMapping& mapping)
        {
            return mapping.key == key;
        });

    return (it != applicationStateIniFileKeyLookup.end()) ? it->value : ApplicationStateIniFileKey::Unknown;
}
