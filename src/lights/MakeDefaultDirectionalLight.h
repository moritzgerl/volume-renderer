/**
* \file MakeDefaultDirectionalLight.h
*
* \brief Factory function for creating a directional light with default properties.
*/

#ifndef MAKE_DEFAULT_DIRECTIONAL_LIGHT_H
#define MAKE_DEFAULT_DIRECTIONAL_LIGHT_H

#include <lights/DirectionalLight.h>

namespace Factory
{
    /**
    * Creates a directional light with default properties.
    *
    * Constructs a DirectionalLight object initialized with default values
    * for direction, ambient color, diffuse color, and specular color. The
    * default directional light provides uniform illumination suitable for
    * volume rendering without requiring user configuration.
    *
    * @return DirectionalLight object with default properties.
    *
    * @see DirectionalLight for directional light implementation.
    * @see UpdateLightingParametersInShader for setting light uniforms.
    */
    DirectionalLight MakeDefaultDirectionalLight();
}

#endif
