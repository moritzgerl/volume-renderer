#ifndef UTILS_H
#define UTILS_H

#include <glm/glm.hpp>

#include <vector>

namespace Utils
{
    void AddPointToCoordinates(const glm::vec3& point, std::vector<float>& coordinates);
}

#endif