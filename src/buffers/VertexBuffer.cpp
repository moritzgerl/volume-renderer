#include <buffers/VertexBuffer.h>
#include <config/Config.h>
#include <primitives/ScreenQuad.h>

#include <glad/glad.h>

VertexBuffer::VertexBuffer(const ScreenQuad& screenQuad)
    : m_vertexBufferObject()
    , m_vertexArrayObject()
    , m_elementBufferObject()
{
    const float* const vertexCoordinates = screenQuad.GetVertexCoordinates();

    glGenVertexArrays(1, &m_vertexArrayObject);
    glGenBuffers(1, &m_vertexBufferObject);
    glBindVertexArray(m_vertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(*vertexCoordinates), vertexCoordinates, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));    
}

VertexBuffer::~VertexBuffer()
{
    glDeleteVertexArrays(1, &m_vertexArrayObject);
    glDeleteBuffers(1, &m_vertexBufferObject);
}

void VertexBuffer::Bind()
{
    glBindVertexArray(m_vertexArrayObject);
}
