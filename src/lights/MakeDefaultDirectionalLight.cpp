#include <lights/MakeDefaultDirectionalLight.h>

DirectionalLight Factory::MakeDefaultDirectionalLight()
{
    DirectionalLight directionalLight;

    directionalLight.direction = glm::vec3{-0.435f, -0.886f, 0.405f};
    directionalLight.ambient = glm::vec3{0.805f};
    directionalLight.diffuse = glm::vec3{0.980f, 0.967f, 0.960f};
    directionalLight.specular = glm::vec3{0.17f};
    directionalLight.intensity = 0.451f;

    return directionalLight;
}
