#include <utils/Utils.h>

void Utils::AddPointToCoordinates(const glm::vec3& point, std::vector<float>& coordinates)
{
    coordinates.push_back(point.x);
    coordinates.push_back(point.y);
    coordinates.push_back(point.z);
}
