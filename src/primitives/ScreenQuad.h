#ifndef SCREEN_QUAD_H
#define SCREEN_QUAD_H

#include <primitives/ScreenQuadVertexCoordinates.h>
#include <buffers/VertexBuffer.h>

#include <memory>

class ScreenQuad
{
public:
    ScreenQuad();
    void Render() const;

private:
    ScreenQuadVertexCoordinates m_vertexCoordinates;
    std::unique_ptr<VertexBuffer> m_vertexBuffer;
};

#endif
