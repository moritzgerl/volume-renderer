/**
* \file ApplicationStateIniFileSection.h
*
* \brief Section identifiers for application state INI file structure.
*/

#ifndef APPLICATION_STATE_INI_FILE_SECTION_H
#define APPLICATION_STATE_INI_FILE_SECTION_H

namespace Persistence
{
    /**
    * \enum ApplicationStateIniFileSection
    *
    * \brief Identifies sections within the application state INI file.
    *
    * Enumerates the different sections used to organize application state
    * parameters in the INI file format. Each section groups related settings
    * such as camera parameters, lighting configuration, SSAO settings, and
    * transfer function control points.
    */
    enum class ApplicationStateIniFileSection
    {
        None,                   /**< No section, used for unrecognized headers. */
        Camera,                 /**< Camera position and orientation parameters. */
        GuiParameters,          /**< GUI-controlled rendering parameters. */
        TransferFunction,       /**< Transfer function configuration. */
        TransferFunctionPoint,  /**< Individual transfer function control point. */
        Trackball,              /**< Trackball camera control settings. */
        SSAO,                   /**< Screen space ambient occlusion parameters. */
        DirectionalLight,       /**< Directional light properties. */
        PointLight,             /**< Point light properties (for indexed lights). */
        Rendering               /**< General rendering settings. */
    };
}

#endif
