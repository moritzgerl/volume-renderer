/**
* \file MakeDefaultGuiParameters.h
*
* \brief Factory function for creating GUI parameters with default values.
*/

#ifndef MAKE_DEFAULT_GUI_PARAMETERS_H
#define MAKE_DEFAULT_GUI_PARAMETERS_H

#include <gui/GuiParameters.h>

namespace Factory
{
    /**
    * Creates GUI parameters with default rendering settings.
    *
    * Constructs a GuiParameters object initialized with default values for
    * all rendering parameters including directional light properties (direction,
    * ambient, diffuse, specular), point light settings (positions, colors,
    * attenuation), SSAO configuration (kernel size, radius, bias, power), and
    * transfer function control points. These defaults provide a reasonable
    * starting point for volume visualization.
    *
    * @return GuiParameters object with default rendering settings.
    *
    * @see GuiParameters for runtime rendering parameters.
    * @see MakeDefaultDirectionalLight for default directional light.
    * @see MakeDefaultPointLights for default point lights.
    * @see MakeDefaultTransferFunction for default transfer function.
    */
    GuiParameters MakeDefaultGuiParameters();
}

#endif