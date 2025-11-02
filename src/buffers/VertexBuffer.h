#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

class ScreenQuadVertexCoordinates;

class VertexBuffer
{
public:
    VertexBuffer(const ScreenQuadVertexCoordinates& screenQuadVertexCoordinates);
    ~VertexBuffer();
    void Bind() const;
    void Unbind() const;

private:
    unsigned int m_vertexBufferObject;
    unsigned int m_vertexArrayObject;
    unsigned int m_elementBufferObject;
};

#endif
