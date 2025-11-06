#include <primitives/UnitCube.h>
#include <glad/glad.h>

UnitCube::UnitCube()
    : m_vertexCoordinates()
    , m_vertexBuffer(m_vertexCoordinates)
{
}

void UnitCube::Render() const
{
    m_vertexBuffer.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    m_vertexBuffer.Unbind();
}
