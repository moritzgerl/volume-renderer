#include <primitives/ScreenQuad.h>
#include <glad/glad.h>

ScreenQuad::ScreenQuad()
    : m_vertexCoordinates()
    , m_vertexBuffer(std::make_unique<VertexBuffer>(m_vertexCoordinates))
{   
}

void  ScreenQuad::Render() const
{
    m_vertexBuffer->Bind();
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    m_vertexBuffer->Unbind();
}
