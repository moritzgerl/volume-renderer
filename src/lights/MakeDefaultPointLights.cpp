#include <lights/MakeDefaultPointLights.h>

std::vector<PointLight> Factory::MakeDefaultPointLights(unsigned int /*numPointLights*/)
{
    return {
        PointLight {
            glm::vec3{15.615f, 3.217f, 3.851f},
            glm::vec3{0.214f},
            glm::vec3{0.381f, 0.579f, 0.514f},
            glm::vec3{0.237f, 0.562f, 0.849f},
            0.466f
        },
        PointLight {
            glm::vec3{16.175f, 3.009f, 10.993f},
            glm::vec3{0.499f, 0.341f, 0.307f},
            glm::vec3{0.511f, 0.381f, 0.579f},
            glm::vec3{0.448f, 0.686f, 0.895f},
            0.230f
        }
    };
}
