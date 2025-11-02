#ifndef UPDATE_LIGHT_SOURCE_MODEL_MATRIX_IN_SHADER_H
#define UPDATE_LIGHT_SOURCE_MODEL_MATRIX_IN_SHADER_H

#include <glm/glm.hpp>

class Shader;

namespace ShaderUtils
{
    void UpdateLightSourceModelMatrixInShader(const glm::vec3& lightPosition, Shader& shader);
}

#endif
