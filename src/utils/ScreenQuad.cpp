#include <utils/ScreenQuad.h>

ScreenQuad::ScreenQuad()
    : m_vertexCoordinates()
    , m_indices()
{
    m_vertexCoordinates =
    {
       -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
       -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
        0.5f,  0.5f, 0.0f, 1.0f, 1.0f
    };

    m_indices =
    {
        0, 1, 2, 3
    };
}

const float* const ScreenQuad::GetVertexCoordinates() const
{
    return &m_vertexCoordinates[0];
}

const unsigned int* const ScreenQuad::GetIndices() const
{
    return &m_indices[0];
}
