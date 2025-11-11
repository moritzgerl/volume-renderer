#ifndef APPLICATION_STATE_INI_FILE_KEY_H
#define APPLICATION_STATE_INI_FILE_KEY_H

namespace Persistence
{
    /// Keys for application state INI file parsing
    enum class ApplicationStateIniFileKey
    {   
        // Common
        PositionX,
        PositionY,
        PositionZ,

        // Camera
        Zoom,

        // Transfer function points
        Value,
        ColorR,
        ColorG,
        ColorB,
        Opacity,

        // Trackball        
        TrackballInvertYAxis,
        TrackballSensitivity,

        // SSAO
        SsaoKernelSize,
        SsaoNoiseSize,
        SsaoRadius,
        SsaoBias,
        SsaoEnable,

        // Lights (shared by directional and point lights)
        DirectionX,
        DirectionY,
        DirectionZ,
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
