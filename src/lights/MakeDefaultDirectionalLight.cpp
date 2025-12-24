#include <lights/MakeDefaultDirectionalLight.h>

DirectionalLight Factory::MakeDefaultDirectionalLight()
{
    return DirectionalLight{
        glm::vec3{-0.435f, -0.886f, 0.405f},
        glm::vec3{0.805f},
        glm::vec3{0.980f, 0.967f, 0.960f},
        glm::vec3{0.17f},
        0.451f
    };
}
