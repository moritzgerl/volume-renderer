#include <buffers/FrameBuffer.h>
#include <config/Config.h>
#include <textures/Texture.h>

#include <glad/glad.h>

#include <iostream>

FrameBuffer::FrameBuffer(FrameBufferId frameBufferId)
    : m_frameBufferId(frameBufferId)
    , m_frameBufferObject()
    , m_renderBufferObjects()
{
    glGenFramebuffers(1, &m_frameBufferObject);
}

FrameBufferId FrameBuffer::GetFrameBufferId() const
{
    return m_frameBufferId;
}

void FrameBuffer::AttachTexture(GLenum attachment, const Texture& texture) const
{   
    glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, texture.GetId(), 0);
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
