#include <data/GetApplicationStateIniFileKey.h>
#include <algorithm>
#include <array>

namespace
{
    struct ApplicationStateIniFileKeyMapping
    {
        std::string_view key;
        Data::ApplicationStateIniFileKey value;
    };

    constexpr std::array<ApplicationStateIniFileKeyMapping, 30> applicationStateIniFileKeyLookup =
    {{
        {"Value", Data::ApplicationStateIniFileKey::Value},
        {"ColorR", Data::ApplicationStateIniFileKey::ColorR},
        {"ColorG", Data::ApplicationStateIniFileKey::ColorG},
        {"ColorB", Data::ApplicationStateIniFileKey::ColorB},
        {"Opacity", Data::ApplicationStateIniFileKey::Opacity},
        {"InvertYAxis", Data::ApplicationStateIniFileKey::InvertYAxis},
        {"Sensitivity", Data::ApplicationStateIniFileKey::Sensitivity},
        {"KernelSize", Data::ApplicationStateIniFileKey::KernelSize},
        {"NoiseSize", Data::ApplicationStateIniFileKey::NoiseSize},
        {"Radius", Data::ApplicationStateIniFileKey::Radius},
        {"Bias", Data::ApplicationStateIniFileKey::Bias},
        {"Enable", Data::ApplicationStateIniFileKey::Enable},
        {"DirectionX", Data::ApplicationStateIniFileKey::DirectionX},
        {"DirectionY", Data::ApplicationStateIniFileKey::DirectionY},
        {"DirectionZ", Data::ApplicationStateIniFileKey::DirectionZ},
        {"PositionX", Data::ApplicationStateIniFileKey::PositionX},
        {"PositionY", Data::ApplicationStateIniFileKey::PositionY},
        {"PositionZ", Data::ApplicationStateIniFileKey::PositionZ},
        {"AmbientR", Data::ApplicationStateIniFileKey::AmbientR},
        {"AmbientG", Data::ApplicationStateIniFileKey::AmbientG},
        {"AmbientB", Data::ApplicationStateIniFileKey::AmbientB},
        {"DiffuseR", Data::ApplicationStateIniFileKey::DiffuseR},
        {"DiffuseG", Data::ApplicationStateIniFileKey::DiffuseG},
        {"DiffuseB", Data::ApplicationStateIniFileKey::DiffuseB},
        {"SpecularR", Data::ApplicationStateIniFileKey::SpecularR},
        {"SpecularG", Data::ApplicationStateIniFileKey::SpecularG},
        {"SpecularB", Data::ApplicationStateIniFileKey::SpecularB},
        {"Intensity", Data::ApplicationStateIniFileKey::Intensity},
        {"ShowLightSources", Data::ApplicationStateIniFileKey::ShowLightSources},
        {"DensityMultiplier", Data::ApplicationStateIniFileKey::DensityMultiplier}
    }};
}

Data::ApplicationStateIniFileKey Data::GetApplicationStateIniFileKey(std::string_view key)
{
    auto it = std::find_if(applicationStateIniFileKeyLookup.begin(), applicationStateIniFileKeyLookup.end(),
        [key](const ApplicationStateIniFileKeyMapping& mapping)
        {
            return mapping.key == key;
        });

    return (it != applicationStateIniFileKeyLookup.end()) ? it->value : ApplicationStateIniFileKey::Unknown;
}
