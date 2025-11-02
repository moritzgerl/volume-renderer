#include <primitives/ScreenQuad.h>

ScreenQuad::ScreenQuad()
    : m_vertexCoordinates()
{
    // Normalized Device Coordinates
    m_vertexCoordinates =
    {
        -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
         1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
         1.0f, -1.0f, 0.0f, 1.0f, 0.0f
    };
}

const float* const ScreenQuad::GetVertexCoordinates() const
{
    return &m_vertexCoordinates[0];
}
