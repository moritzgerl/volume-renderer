#ifndef SCREEN_QUAD_VERTEX_COORDINATES_H
#define SCREEN_QUAD_VERTEX_COORDINATES_H

#include <vector>

class ScreenQuadVertexCoordinates
{
public:
    ScreenQuadVertexCoordinates();
    const float* const Get() const;

private:
    std::vector<float> m_vertexCoordinates;
};

#endif
