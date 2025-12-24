#include <buffers/FrameBuffer.h>
#include <config/Config.h>
#include <textures/Texture.h>

#include <glad/glad.h>

#include <iostream>
#include <utility>

FrameBuffer::FrameBuffer(FrameBufferId frameBufferId)
    : m_frameBufferId{frameBufferId}
    , m_frameBufferObject{0}
    , m_renderBufferObjects{}
{
    if (frameBufferId != FrameBufferId::Default)
    {
        glGenFramebuffers(1, &m_frameBufferObject);
    }
}

FrameBuffer::~FrameBuffer()
{
    if (m_frameBufferObject != 0)
    {
        glDeleteFramebuffers(1, &m_frameBufferObject);
    }
    if (!m_renderBufferObjects.empty())
    {
        glDeleteRenderbuffers(static_cast<GLsizei>(m_renderBufferObjects.size()), m_renderBufferObjects.data());
    }
}

FrameBuffer::FrameBuffer(FrameBuffer&& other) noexcept
    : m_frameBufferId{other.m_frameBufferId}
    , m_frameBufferObject{other.m_frameBufferObject}
    , m_renderBufferObjects{std::move(other.m_renderBufferObjects)}
{
    other.m_frameBufferObject = 0;
}

FrameBuffer& FrameBuffer::operator=(FrameBuffer&& other) noexcept
{
    if (this != &other)
    {
        if (m_frameBufferObject != 0)
        {
            glDeleteFramebuffers(1, &m_frameBufferObject);
        }
        if (!m_renderBufferObjects.empty())
        {
            glDeleteRenderbuffers(static_cast<GLsizei>(m_renderBufferObjects.size()), m_renderBufferObjects.data());
        }

        m_frameBufferId = other.m_frameBufferId;
        m_frameBufferObject = other.m_frameBufferObject;
        m_renderBufferObjects = std::move(other.m_renderBufferObjects);

        other.m_frameBufferObject = 0;
    }
    return *this;
}

FrameBufferId FrameBuffer::GetId() const
{
    return m_frameBufferId;
}

void FrameBuffer::AttachTexture(GLenum attachment, const Texture& texture)
{
    glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, texture.GetGlId(), 0);
}

void FrameBuffer::AttachRenderBuffer(GLenum attachment, GLenum internalFormat, unsigned int width, unsigned int height)
{
    unsigned int renderBufferObject;
    glGenRenderbuffers(1, &renderBufferObject);
    glBindRenderbuffer(GL_RENDERBUFFER, renderBufferObject);
    glRenderbufferStorage(GL_RENDERBUFFER, internalFormat, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, renderBufferObject);
    m_renderBufferObjects.push_back(renderBufferObject);
}

void FrameBuffer::Bind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferObject);
}

void FrameBuffer::Unbind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::Check() const
{
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "Framebuffer not complete!" << std::endl;
    }
}
