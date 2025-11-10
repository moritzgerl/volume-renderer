#include <data/GetGuiParametersKey.h>
#include <algorithm>
#include <array>

namespace
{
    struct GuiParametersKeyMapping
    {
        std::string_view key;
        Data::GuiParametersKey value;
    };

    constexpr std::array<GuiParametersKeyMapping, 30> guiParametersKeyLookup =
    {{
        {"Value", Data::GuiParametersKey::Value},
        {"ColorR", Data::GuiParametersKey::ColorR},
        {"ColorG", Data::GuiParametersKey::ColorG},
        {"ColorB", Data::GuiParametersKey::ColorB},
        {"Opacity", Data::GuiParametersKey::Opacity},
        {"InvertYAxis", Data::GuiParametersKey::InvertYAxis},
        {"Sensitivity", Data::GuiParametersKey::Sensitivity},
        {"KernelSize", Data::GuiParametersKey::KernelSize},
        {"NoiseSize", Data::GuiParametersKey::NoiseSize},
        {"Radius", Data::GuiParametersKey::Radius},
        {"Bias", Data::GuiParametersKey::Bias},
        {"Enable", Data::GuiParametersKey::Enable},
        {"DirectionX", Data::GuiParametersKey::DirectionX},
        {"DirectionY", Data::GuiParametersKey::DirectionY},
        {"DirectionZ", Data::GuiParametersKey::DirectionZ},
        {"PositionX", Data::GuiParametersKey::PositionX},
        {"PositionY", Data::GuiParametersKey::PositionY},
        {"PositionZ", Data::GuiParametersKey::PositionZ},
        {"AmbientR", Data::GuiParametersKey::AmbientR},
        {"AmbientG", Data::GuiParametersKey::AmbientG},
        {"AmbientB", Data::GuiParametersKey::AmbientB},
        {"DiffuseR", Data::GuiParametersKey::DiffuseR},
        {"DiffuseG", Data::GuiParametersKey::DiffuseG},
        {"DiffuseB", Data::GuiParametersKey::DiffuseB},
        {"SpecularR", Data::GuiParametersKey::SpecularR},
        {"SpecularG", Data::GuiParametersKey::SpecularG},
        {"SpecularB", Data::GuiParametersKey::SpecularB},
        {"Intensity", Data::GuiParametersKey::Intensity},
        {"ShowLightSources", Data::GuiParametersKey::ShowLightSources},
        {"DensityMultiplier", Data::GuiParametersKey::DensityMultiplier}
    }};
}

Data::GuiParametersKey Data::GetGuiParametersKey(std::string_view key)
{
    auto it = std::find_if(guiParametersKeyLookup.begin(), guiParametersKeyLookup.end(),
        [key](const GuiParametersKeyMapping& mapping)
        {
            return mapping.key == key;
        });

    return (it != guiParametersKeyLookup.end()) ? it->value : GuiParametersKey::Unknown;
}
