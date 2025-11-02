#include <buffers/VertexBuffer.h>
#include <config/Config.h>
#include <utils/ScreenQuad.h>

#include <glad/glad.h>

VertexBuffer::VertexBuffer(const ScreenQuad& screenQuad)
    : m_vertexBufferObject()
    , m_vertexArrayObject()
    , m_elementBufferObject()
{
    glGenVertexArrays(1, &m_vertexArrayObject);
    glGenBuffers(1, &m_vertexBufferObject);
    glGenBuffers(1, &m_elementBufferObject);

    glBindVertexArray(m_vertexArrayObject);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, 20 * sizeof(float), screenQuad.GetVertexCoordinates(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), screenQuad.GetIndices(), GL_STATIC_DRAW);
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
