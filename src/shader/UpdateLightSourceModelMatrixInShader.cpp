#include <shader/UpdateLightSourceModelMatrixInShader.h>
#include <shader/Shader.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Constants
{
    const glm::mat4 lightSourceCubeScalingMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.2f));
}

void ShaderUtils::UpdateLightSourceModelMatrixInShader(const glm::vec3& lightPosition, const Shader& shader)
{
    glm::mat4 model = glm::translate(glm::mat4(1.0f), lightPosition) * Constants::lightSourceCubeScalingMatrix;
    shader.setMat4("model", model);
}
