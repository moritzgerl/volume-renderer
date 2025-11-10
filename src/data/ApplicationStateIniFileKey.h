#ifndef APPLICATION_STATE_INI_FILE_KEY_H
#define APPLICATION_STATE_INI_FILE_KEY_H

namespace Data
{
    /// Keys for application state INI file parsing
    enum class ApplicationStateIniFileKey
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
