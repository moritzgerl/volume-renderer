#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

class ScreenQuadVertexCoordinates;
class UnitCubeVertexCoordinates;

class VertexBuffer
{
public:
    VertexBuffer(const ScreenQuadVertexCoordinates& screenQuadVertexCoordinates);
    VertexBuffer(const UnitCubeVertexCoordinates& unitCubeVertexCoordinates);

    // TODO use C++26 concepts
    VertexBuffer(const VertexBuffer&) = delete;
    VertexBuffer(VertexBuffer&& other) noexcept;

    VertexBuffer& operator=(const VertexBuffer&) = delete;    
    VertexBuffer& operator=(VertexBuffer&& other) noexcept;

    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;

private:
    unsigned int m_vertexBufferObject;
    unsigned int m_vertexArrayObject;
    unsigned int m_elementBufferObject;
};

#endif
