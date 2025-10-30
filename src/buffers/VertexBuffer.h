#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

class UnitPlane;

class VertexBuffer
{
public:
    VertexBuffer(const UnitPlane& plane);
    ~VertexBuffer();
    void Bind();

private:
    unsigned int m_vertexBufferObject;
    unsigned int m_vertexArrayObject;
    unsigned int m_elementBufferObject;
};

#endif
