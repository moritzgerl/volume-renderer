#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

#include <vector>

class Texture;

class FrameBuffer
{
public:
    FrameBuffer();
    void AttachTexture(unsigned int attachment, const Texture& texture);
    void AttachRenderBuffer(unsigned int attachment, unsigned int internalFormat, unsigned int width, unsigned int height);
    void Bind();
    void Unbind();
    void Check();
    
private:
    unsigned int m_frameBufferObject;
    std::vector<unsigned int> m_renderBufferObjects;
};

#endif
