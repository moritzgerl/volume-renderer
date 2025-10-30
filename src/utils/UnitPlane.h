#ifndef UNIT_PLANE_H
#define UNIT_PLANE_H

#include <vector>

class UnitPlane
{
public:
    UnitPlane();
    const float* const GetVertexCoordinates() const;
    const unsigned int* const GetIndices() const;

private:
    std::vector<float> m_vertexCoordinates;
    std::vector<unsigned int> m_indices;
};

#endif
