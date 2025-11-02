#ifndef SCREEN_QUAD_H
#define SCREEN_QUAD_H

#include <vector>

class ScreenQuad
{
public:
    ScreenQuad();
    const float* const GetVertexCoordinates() const;

private:
    std::vector<float> m_vertexCoordinates;
};

#endif
