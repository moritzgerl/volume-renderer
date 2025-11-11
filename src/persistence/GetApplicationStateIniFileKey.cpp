#include <persistence/GetApplicationStateIniFileKey.h>
#include <algorithm>
#include <array>

namespace
{
    using Key = Persistence::ApplicationStateIniFileKey;

    struct ApplicationStateIniFileKeyMapping
    {
        std::string_view stringKey;
        Key enumKey;
    };

    constexpr std::array<ApplicationStateIniFileKeyMapping, 31> applicationStateIniFileKeyLookup =
    {{  
        {"PositionX", Key::PositionX},
        {"PositionY", Key::PositionY},
        {"PositionZ", Key::PositionZ},
        {"Zoom", Key::Zoom},
        {"Value", Key::Value},
        {"ColorR", Key::ColorR},
        {"ColorG", Key::ColorG},
        {"ColorB", Key::ColorB},
        {"Opacity", Key::Opacity},
        {"TrackballInvertYAxis", Key::TrackballInvertYAxis},
        {"TrackballSensitivity", Key::TrackballSensitivity},
        {"SsaoKernelSize", Key::SsaoKernelSize},
        {"SsaoNoiseSize", Key::SsaoNoiseSize},
        {"SsaoRadius", Key::SsaoRadius},
        {"SsaoBias", Key::SsaoBias},
        {"SsaoEnable", Key::SsaoEnable},
        {"DirectionX", Key::DirectionX},
        {"DirectionY", Key::DirectionY},
        {"DirectionZ", Key::DirectionZ},
        {"AmbientR", Key::AmbientR},
        {"AmbientG", Key::AmbientG},
        {"AmbientB", Key::AmbientB},
        {"DiffuseR", Key::DiffuseR},
        {"DiffuseG", Key::DiffuseG},
        {"DiffuseB", Key::DiffuseB},
        {"SpecularR", Key::SpecularR},
        {"SpecularG", Key::SpecularG},
        {"SpecularB", Key::SpecularB},
        {"Intensity", Key::Intensity},
        {"ShowLightSources", Key::ShowLightSources},
        {"DensityMultiplier", Key::DensityMultiplier}
    }};
}

Persistence::ApplicationStateIniFileKey Persistence::GetApplicationStateIniFileKey(std::string_view stringKey)
{
    auto it = std::find_if(applicationStateIniFileKeyLookup.begin(), applicationStateIniFileKeyLookup.end(),
        [stringKey](const ApplicationStateIniFileKeyMapping& mapping)
        {
            return mapping.stringKey == stringKey;
        });

    return (it != applicationStateIniFileKeyLookup.end()) ? it->enumKey : ApplicationStateIniFileKey::Unknown;
}
