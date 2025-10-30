#include <lights/MakeDefaultPointLights.h>

std::vector<PointLight> MakeDefaultPointLights(unsigned int numPointLights)
{
    std::vector<PointLight> pointLights(numPointLights);

    pointLights[0].position = glm::vec3(15.615f, 3.217f, 3.851f);
    pointLights[0].ambient = glm::vec3(0.214f);
    pointLights[0].diffuse = glm::vec3(0.381f, 0.579f, 0.514f);
    pointLights[0].specular = glm::vec3(0.237f, 0.562f, 0.849f);
    pointLights[0].intensity = 0.466f;

    pointLights[1].position = glm::vec3(16.175f, 3.009f, 10.993f);
    pointLights[1].ambient = glm::vec3(0.499f, 0.341f, 0.307f);
    pointLights[1].diffuse = glm::vec3(0.511f, 0.381f, 0.579f);
    pointLights[1].specular = glm::vec3(0.448f, 0.686f, 0.895f);
    pointLights[1].intensity = 0.230f;

    return pointLights;
}
