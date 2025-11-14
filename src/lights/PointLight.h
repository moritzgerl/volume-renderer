/**
* \file PointLight.h
*
* \brief Point light parameters for lighting calculations.
*/

#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include <glm/glm.hpp>

/**
* \struct PointLight
*
* \brief Parameters for a point light source.
*
* Represents a light source at a specific position in 3D space that radiates
* in all directions. Contains ambient, diffuse, and specular color components
* along with intensity and position.
*
* Default values are provided via Factory::MakeDefaultPointLights().
* Parameters can be adjusted at runtime through the GUI.
*
* @see Factory::MakeDefaultPointLights for default light configuration.
* @see GuiParameters for storing point light parameters.
* @see UpdateLightingParametersInShader for passing light data to shaders.
*/
struct PointLight
{
    glm::vec3 position; /**< Light position in world space. */
    glm::vec3 ambient; /**< Ambient color component. */
    glm::vec3 diffuse; /**< Diffuse color component. */
    glm::vec3 specular; /**< Specular color component. */
    float intensity; /**< Light intensity multiplier. */
};

#endif
