/**
* \file MakeDefaultPointLights.h
*
* \brief Factory function for creating point lights with default properties.
*/

#ifndef MAKE_DEFAULT_POINT_LIGHTS_H
#define MAKE_DEFAULT_POINT_LIGHTS_H

#include <vector>

#include <lights/PointLight.h>

namespace Factory
{
    /**
    * Creates a collection of point lights with default properties.
    *
    * Constructs a vector of PointLight objects initialized with default values
    * for position, ambient color, diffuse color, specular color, and attenuation
    * parameters (constant, linear, quadratic). The point lights are positioned
    * around the volume to provide balanced illumination from multiple directions.
    *
    * @param numPointLights Number of point lights to create.
    * @return Vector of PointLight objects with default properties.
    *
    * @see PointLight for point light implementation.
    * @see UpdateLightingParametersInShader for setting light uniforms.
    */
    std::vector<PointLight> MakeDefaultPointLights(unsigned int numPointLights);
}

#endif
