#include <lights/GetLightSpaceMatrix.h>

#include <gui/GuiParameters.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 GetLightSpaceMatrix(const GuiParameters& guiParameters)
{
    const float size = 40.0f;
    const glm::vec3 lightPosition = -guiParameters.directionalLight.direction * 2.0f;
    const glm::mat4 lightProjection = glm::ortho(-size, size, -size, size, -size, size);
    const glm::mat4 lightView = glm::lookAt(lightPosition, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
    const glm::mat4 lightSpace = lightProjection * lightView;
    return lightSpace;
}
