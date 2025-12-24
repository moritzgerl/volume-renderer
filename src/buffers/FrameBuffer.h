/**
* \file FrameBuffer.h
*
* \brief Framebuffer object (FBO) abstraction for off-screen rendering.
*/

#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

#include <buffers/FrameBufferId.h>
#include <vector>

class Texture;

/**
* \class FrameBuffer
*
* \brief Simplifies OpenGL framebuffer creation and attachment management.
*
* Encapsulates an OpenGL framebuffer object (FBO) along with any associated renderbuffer objects.
* Provides methods for attaching textures and renderbuffers, binding/unbinding, and checking
* framebuffer completeness.
*
* Each FrameBuffer is identified by a FrameBufferId for type-safe retrieval from Storage.
* FrameBuffers are created via Factory::MakeFrameBuffers() which configures all framebuffers
* needed for the rendering pipeline.
*
* @see FrameBufferId for the enumeration of framebuffer types.
* @see Factory::MakeFrameBuffers for construction of framebuffers.
* @see RenderPass for using framebuffers during rendering.
*/
class FrameBuffer
{
public:
    /**
    * Constructor.
    * @param frameBufferId The ID identifying this framebuffer.
    */
    FrameBuffer(FrameBufferId frameBufferId);

    ~FrameBuffer();
    FrameBuffer(const FrameBuffer&) = delete;
    FrameBuffer& operator=(const FrameBuffer&) = delete;
    FrameBuffer(FrameBuffer&&) noexcept;
    FrameBuffer& operator=(FrameBuffer&&) noexcept;

    FrameBufferId GetId() const;

    /**
    * Attaches a texture to the framebuffer at the specified attachment point.
    * @param attachment The attachment point (e.g., GL_COLOR_ATTACHMENT0, GL_DEPTH_ATTACHMENT).
    * @param texture The texture to attach.
    * @return void
    */
    void AttachTexture(unsigned int attachment, const Texture& texture);

    /**
    * Creates and attaches a renderbuffer to the framebuffer.
    * @param attachment The attachment point (e.g., GL_DEPTH_STENCIL_ATTACHMENT).
    * @param internalFormat The internal format of the renderbuffer (e.g., GL_DEPTH24_STENCIL8).
    * @param width The width of the renderbuffer in pixels.
    * @param height The height of the renderbuffer in pixels.
    * @return void
    */
    void AttachRenderBuffer(unsigned int attachment, unsigned int internalFormat, unsigned int width, unsigned int height);

    /**
    * Binds this framebuffer for rendering.
    * @return void
    */
    void Bind() const;

    /**
    * Unbinds this framebuffer (binds the default framebuffer).
    * @return void
    */
    void Unbind() const;

    /**
    * Checks framebuffer completeness and throws an exception if incomplete.
    * @return void
    */
    void Check() const;

private:
    FrameBufferId m_frameBufferId; /**< The ID of this framebuffer for identification. */
    unsigned int m_frameBufferObject; /**< The OpenGL framebuffer object handle. */
    std::vector<unsigned int> m_renderBufferObjects; /**< Renderbuffer object handles owned by this framebuffer. */
};

#endif
