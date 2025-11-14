/**
* \file GuiParameters.h
*
* \brief GUI parameter structure for storing runtime-adjustable settings.
*/

#ifndef GUI_PARAMETERS_H
#define GUI_PARAMETERS_H

#include <lights/DirectionalLight.h>
#include <lights/PointLight.h>
#include <transferfunction/TransferFunction.h>

#include <vector>

/**
* \struct GuiParameters
*
* \brief Stores all runtime-adjustable parameters exposed through the GUI.
*
* Contains parameters for lighting, SSAO, transfer function, camera controls,
* and volume rendering. These values are modified by the Gui class and used
* to update shader uniforms during rendering.
*
* Default values are set via Factory::MakeGuiParameters() using constants
* from the Config namespace. Parameters can be persisted to/from INI files.
*
* @see Gui for the interface that modifies these parameters.
* @see Factory::MakeGuiParameters for initialization with default values.
* @see LoadApplicationStateFromIniFile for loading parameters from disk.
* @see SaveApplicationStateToIniFile for saving parameters to disk.
*/
struct GuiParameters
{
    TransferFunction transferFunction; /**< Transfer function control points for volume rendering. */
    bool showLightSources; /**< Whether to render light source visualizations. */
    DirectionalLight directionalLight; /**< Directional light parameters. */
    std::vector<PointLight> pointLights; /**< Point light parameters. */
    unsigned int ssaoKernelSize; /**< Number of samples in the SSAO kernel. */
    unsigned int ssaoNoiseSize; /**< Size of the SSAO noise texture. */
    float ssaoRadius; /**< Sampling radius for SSAO. */
    float ssaoBias; /**< Depth bias to reduce SSAO artifacts. */
    bool enableSsao; /**< Whether SSAO is enabled. */
    bool trackballInvertYAxis; /**< Whether to invert the Y-axis for trackball controls. */
    float trackballSensitivity; /**< Sensitivity multiplier for trackball rotation. */
    float raycastingDensityMultiplier; /**< Density multiplier for volume ray-casting. */
};

#endif
