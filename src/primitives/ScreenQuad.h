#ifndef SCREEN_QUAD_H
#define SCREEN_QUAD_H

#include <primitives/ScreenQuadVertexCoordinates.h>
#include <buffers/VertexBuffer.h>

class ScreenQuad
{
public:
    ScreenQuad();
    void Render() const;

private:
    ScreenQuadVertexCoordinates m_vertexCoordinates;
    VertexBuffer m_vertexBuffer;
};

#endif
