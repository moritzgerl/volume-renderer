#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

class ScreenQuad;

class VertexBuffer
{
public:
    VertexBuffer(const ScreenQuad& screenQuad);
    ~VertexBuffer();
    void Bind();

private:
    unsigned int m_vertexBufferObject;
    unsigned int m_vertexArrayObject;
    unsigned int m_elementBufferObject;
};

#endif
