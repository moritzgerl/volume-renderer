#include <shader/UpdateMatricesInShader.h>
#include <shader/Shader.h>
#include <camera/Camera.h>
#include <config/Config.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void ShaderUtils::UpdateMatricesInShader(const Camera& camera, Shader& shader)
{
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), static_cast<float>(Config::windowWidth) / static_cast<float>(Config::windowHeight), 0.1f, 100.0f);
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 model = glm::mat4(1.0f);

    shader.setMat4("projection", projection);
    shader.setMat4("view", view);
    shader.setMat4("model", model);
}
