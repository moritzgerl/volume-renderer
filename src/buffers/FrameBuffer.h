#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

#include <buffers/FrameBufferId.h>
#include <vector>

class Texture;

class FrameBuffer
{
public:
    FrameBuffer(FrameBufferId frameBufferId);
    FrameBufferId GetId() const;
    void AttachTexture(unsigned int attachment, const Texture& texture) const;
    void AttachRenderBuffer(unsigned int attachment, unsigned int internalFormat, unsigned int width, unsigned int height);
    void Bind() const;
    void Unbind() const;
    void Check() const;

private:
    FrameBufferId m_frameBufferId;
    unsigned int m_frameBufferObject;
    std::vector<unsigned int> m_renderBufferObjects;
};

#endif
