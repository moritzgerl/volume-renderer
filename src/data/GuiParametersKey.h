#ifndef GUI_PARAMETERS_KEY_H
#define GUI_PARAMETERS_KEY_H

namespace Data
{
    /// Keys for GUI parameters file parsing
    enum class GuiParametersKey
    {
        // Transfer function point keys
        Value,
        ColorR,
        ColorG,
        ColorB,
        Opacity,

        // Camera keys
        InvertYAxis,
        Sensitivity,

        // SSAO keys
        KernelSize,
        NoiseSize,
        Radius,
        Bias,
        Enable,

        // Light keys (shared by directional and point lights)
        DirectionX,
        DirectionY,
        DirectionZ,
        PositionX,
        PositionY,
        PositionZ,
        AmbientR,
        AmbientG,
        AmbientB,
        DiffuseR,
        DiffuseG,
        DiffuseB,
        SpecularR,
        SpecularG,
        SpecularB,
        Intensity,

        // Rendering keys
        ShowLightSources,
        DensityMultiplier,

        Unknown
    };
}

#endif
