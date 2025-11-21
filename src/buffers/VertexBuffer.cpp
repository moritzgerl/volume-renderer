#include <buffers/VertexBuffer.h>
#include <config/Config.h>
#include <primitives/ScreenQuadVertexCoordinates.h>
#include <primitives/UnitCubeVertexCoordinates.h>

#include <glad/glad.h>

VertexBuffer::VertexBuffer(const ScreenQuadVertexCoordinates& screenQuadVertexCoordinates)
    : m_vertexBufferObject{}
    , m_vertexArrayObject{}
    , m_elementBufferObject{}
{
    const float* const vertexCoordinates = screenQuadVertexCoordinates.Get();
    const size_t sizeInBytes = screenQuadVertexCoordinates.GetSizeInBytes();

    glGenVertexArrays(1, &m_vertexArrayObject);
    glGenBuffers(1, &m_vertexBufferObject);
    glBindVertexArray(m_vertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeInBytes, vertexCoordinates, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::VertexBuffer(const UnitCubeVertexCoordinates& unitCubeVertexCoordinates)
    : m_vertexBufferObject{}
    , m_vertexArrayObject{}
    , m_elementBufferObject{}
{
    const float* const vertexCoordinates = unitCubeVertexCoordinates.Get();
    const size_t sizeInBytes = unitCubeVertexCoordinates.GetSizeInBytes();

    glGenVertexArrays(1, &m_vertexArrayObject);
    glGenBuffers(1, &m_vertexBufferObject);

    glBindVertexArray(m_vertexArrayObject);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeInBytes, vertexCoordinates, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept
    : m_vertexBufferObject{other.m_vertexBufferObject}
    , m_vertexArrayObject{other.m_vertexArrayObject}
    , m_elementBufferObject{other.m_elementBufferObject}
{
    other.m_vertexBufferObject = 0;
    other.m_vertexArrayObject = 0;
    other.m_elementBufferObject = 0;
}

VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) noexcept
{
    if (this != &other)
    {
        if (m_vertexArrayObject != 0)
        {
            glDeleteVertexArrays(1, &m_vertexArrayObject);
        }
        if (m_vertexBufferObject != 0)
        {
            glDeleteBuffers(1, &m_vertexBufferObject);
        }

        m_vertexBufferObject = other.m_vertexBufferObject;
        m_vertexArrayObject = other.m_vertexArrayObject;
        m_elementBufferObject = other.m_elementBufferObject;

        other.m_vertexBufferObject = 0;
        other.m_vertexArrayObject = 0;
        other.m_elementBufferObject = 0;
    }
    return *this;
}

VertexBuffer::~VertexBuffer()
{
    if (m_vertexArrayObject != 0)
    {
        glDeleteVertexArrays(1, &m_vertexArrayObject);
    }
    if (m_vertexBufferObject != 0)
    {
        glDeleteBuffers(1, &m_vertexBufferObject);
    }
}

void VertexBuffer::Bind() const
{
    glBindVertexArray(m_vertexArrayObject);
}

void VertexBuffer::Unbind() const
{
    glBindVertexArray(0);
}
