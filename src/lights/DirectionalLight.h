/**
* \file DirectionalLight.h
*
* \brief Directional light parameters for lighting calculations.
*/

#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include <glm/glm.hpp>

/**
* \struct DirectionalLight
*
* \brief Parameters for a directional light source.
*
* Represents a light source at infinite distance with uniform direction,
* such as sunlight. Contains ambient, diffuse, and specular color components
* along with intensity and direction.
*
* Default values are provided via Factory::MakeDefaultDirectionalLight().
* Parameters can be adjusted at runtime through the GUI.
*
* @see Factory::MakeDefaultDirectionalLight for default light configuration.
* @see GuiParameters for storing directional light parameters.
* @see UpdateLightingParametersInShader for passing light data to shaders.
*/
struct DirectionalLight
{
    glm::vec3 direction; /**< Light direction vector (normalized). */
    glm::vec3 ambient; /**< Ambient color component. */
    glm::vec3 diffuse; /**< Diffuse color component. */
    glm::vec3 specular; /**< Specular color component. */
    float intensity; /**< Light intensity multiplier. */
};

#endif
