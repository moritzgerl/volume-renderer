/**
* \file MakeFrameBuffers.h
*
* \brief Factory function for creating all framebuffers used in the rendering pipeline.
*/

#ifndef MAKE_FRAME_BUFFERS_H
#define MAKE_FRAME_BUFFERS_H

#include <buffers/FrameBuffer.h>
#include <storage/StorageTypes.h>
#include <vector>

namespace Factory
{
    /**
    * Creates and configures all framebuffers for the rendering pipeline.
    *
    * Constructs framebuffer objects for various rendering passes including
    * SSAO input (G-buffer), SSAO computation, and SSAO blur. Each framebuffer
    * is configured with appropriate texture attachments from the texture storage.
    * The framebuffers are indexed by FrameBufferId enum values.
    *
    * @param textureStorage Storage containing all texture resources for attachments.
    * @return Vector of configured FrameBuffer objects indexed by FrameBufferId.
    *
    * @see FrameBuffer for framebuffer object abstraction.
    * @see FrameBufferId for framebuffer identifier enumeration.
    * @see MakeTextures for creating texture resources.
    */
    std::vector<FrameBuffer> MakeFrameBuffers(const TextureStorage& textureStorage);
}

#endif
