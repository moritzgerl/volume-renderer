/**
* \file UpdateLightSourceModelMatrixInShader.h
*
* \brief Utility for updating light source model matrix in shaders.
*/

#ifndef UPDATE_LIGHT_SOURCE_MODEL_MATRIX_IN_SHADER_H
#define UPDATE_LIGHT_SOURCE_MODEL_MATRIX_IN_SHADER_H

#include <glm/glm.hpp>

class Shader;

namespace ShaderUtils
{
    /**
    * Updates the model matrix for light source visualization.
    *
    * Sets the model matrix uniform in the shader for rendering light
    * source visualization geometry (typically a small sphere or icon)
    * at the light's position in world space.
    *
    * This function should be called before rendering light source
    * visualization geometry in the LightSource render pass.
    *
    * @param lightPosition Position of the light in world coordinates.
    * @param shader The shader to update with the model matrix.
    * @return void
    *
    * @see UpdateLightingParametersInShader for setting light properties.
    * @see Shader for shader uniform management.
    */
    void UpdateLightSourceModelMatrixInShader(const glm::vec3& lightPosition, const Shader& shader);
}

#endif
