/**
* \file ApplicationStateIniFileKey.h
*
* \brief Key identifiers for application state INI file parameters.
*/

#ifndef APPLICATION_STATE_INI_FILE_KEY_H
#define APPLICATION_STATE_INI_FILE_KEY_H

namespace Persistence
{
    /**
    * \enum ApplicationStateIniFileKey
    *
    * \brief Identifies parameter keys within INI file sections.
    *
    * Enumerates all parameter keys used in the application state INI file.
    * Keys are organized by category (camera, transfer function, SSAO, lighting,
    * rendering) and map to specific configuration values within each section.
    */
    enum class ApplicationStateIniFileKey
    {
        // Common position coordinates
        PositionX,              /**< X-coordinate for positions (camera, lights). */
        PositionY,              /**< Y-coordinate for positions (camera, lights). */
        PositionZ,              /**< Z-coordinate for positions (camera, lights). */

        // Camera parameters
        Zoom,                   /**< Camera zoom level. */

        // Transfer function control point parameters
        Value,                  /**< Scalar value for transfer function control point. */
        ColorR,                 /**< Red color component (0-1). */
        ColorG,                 /**< Green color component (0-1). */
        ColorB,                 /**< Blue color component (0-1). */
        Opacity,                /**< Opacity/alpha value (0-1). */

        // Trackball camera control parameters
        TrackballInvertYAxis,   /**< Whether to invert Y-axis for trackball rotation. */
        TrackballSensitivity,   /**< Trackball rotation sensitivity. */

        // Screen space ambient occlusion parameters
        SsaoKernelSize,         /**< Number of samples in SSAO kernel. */
        SsaoNoiseSize,          /**< Size of SSAO noise texture. */
        SsaoRadius,             /**< SSAO sampling radius. */
        SsaoBias,               /**< SSAO depth bias to prevent acne. */
        SsaoEnable,             /**< Whether SSAO is enabled. */

        // Lighting parameters (shared by directional and point lights)
        DirectionX,             /**< X-component of light direction. */
        DirectionY,             /**< Y-component of light direction. */
        DirectionZ,             /**< Z-component of light direction. */
        AmbientR,               /**< Red component of ambient color. */
        AmbientG,               /**< Green component of ambient color. */
        AmbientB,               /**< Blue component of ambient color. */
        DiffuseR,               /**< Red component of diffuse color. */
        DiffuseG,               /**< Green component of diffuse color. */
        DiffuseB,               /**< Blue component of diffuse color. */
        SpecularR,              /**< Red component of specular color. */
        SpecularG,              /**< Green component of specular color. */
        SpecularB,              /**< Blue component of specular color. */
        Intensity,              /**< Light intensity multiplier. */

        // General rendering parameters
        ShowLightSources,       /**< Whether to render light source visualizations. */
        DensityMultiplier,      /**< Volume density multiplier for rendering. */

        Unknown                 /**< Unrecognized key. */
    };
}

#endif
