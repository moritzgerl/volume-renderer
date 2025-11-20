#include <shader/UpdateCameraMatricesInShader.h>
#include <shader/Shader.h>
#include <camera/Camera.h>
#include <config/Config.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void ShaderUtils::UpdateCameraMatricesInShader(const Camera& camera, const Shader& shader, float viewportWidth, float viewportHeight)
{
    const glm::mat4 projection = glm::perspective(glm::radians(camera.GetZoom()), viewportWidth / viewportHeight, 0.1f, 100.0f);
    const glm::mat4 view = camera.GetViewMatrix();
    const glm::mat4 model = glm::mat4(1.0f);

    shader.SetMat4("projection", projection);
    shader.SetMat4("view", view);
    shader.SetMat4("model", model);
}
