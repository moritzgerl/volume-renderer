#ifndef SCREEN_QUAD_H
#define SCREEN_QUAD_H

#include <vector>

class ScreenQuad
{
public:
    ScreenQuad();
    const float* const GetVertexCoordinates() const;
    const unsigned int* const GetIndices() const;

private:
    std::vector<float> m_vertexCoordinates;
    std::vector<unsigned int> m_indices;
};

#endif
