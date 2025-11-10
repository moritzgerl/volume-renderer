#ifndef APPLICATION_STATE_INI_FILE_KEY_H
#define APPLICATION_STATE_INI_FILE_KEY_H

namespace Data
{
    /// Keys for application state INI file parsing
    enum class ApplicationStateIniFileKey
    {   
        // Transfer function points
        Value,
        ColorR,
        ColorG,
        ColorB,
        Opacity,

        // Camera parameters
        Zoom,
        InvertYAxis,
        Sensitivity,

        // SSAO
        KernelSize,
        NoiseSize,
        Radius,
        Bias,
        Enable,

        // Lights (shared by directional and point lights)
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

        // Rendering
        ShowLightSources,
        DensityMultiplier,

        Unknown
    };
}

#endif
