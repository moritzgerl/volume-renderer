#ifndef UNIT_CUBE_VERTEX_COORDINATES_H
#define UNIT_CUBE_VERTEX_COORDINATES_H

#include <vector>

class UnitCubeVertexCoordinates
{
public:
    UnitCubeVertexCoordinates();
    const float* const Get() const;

private:
    std::vector<float> m_vertexCoordinates;
};

#endif
