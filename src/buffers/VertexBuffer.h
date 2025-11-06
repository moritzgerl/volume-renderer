#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

class ScreenQuadVertexCoordinates;
class UnitCubeVertexCoordinates;

class VertexBuffer
{
public:
    VertexBuffer(const ScreenQuadVertexCoordinates& screenQuadVertexCoordinates);
    VertexBuffer(const UnitCubeVertexCoordinates& unitCubeVertexCoordinates);
    ~VertexBuffer();
    void Bind() const;
    void Unbind() const;

private:
    unsigned int m_vertexBufferObject;
    unsigned int m_vertexArrayObject;
    unsigned int m_elementBufferObject;
};

#endif
