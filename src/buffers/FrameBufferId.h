/**
* \file FrameBufferId.h
*
* \brief Enumeration of framebuffer objects used in the rendering pipeline.
*/

#ifndef FRAME_BUFFER_ID_H
#define FRAME_BUFFER_ID_H

/**
* \enum FrameBufferId
*
* \brief Identifies framebuffer objects for off-screen rendering.
*
* Each framebuffer ID corresponds to a framebuffer object (FBO) created via
* MakeFrameBuffers and stored in Storage. Framebuffers are used for multi-pass
* rendering, allowing render passes to write to textures that are later used
* as inputs to subsequent passes.
*
* @see FrameBuffer for framebuffer abstraction.
* @see MakeFrameBuffers for framebuffer creation.
* @see Storage for framebuffer storage and retrieval.
*/
enum class FrameBufferId
{
    SsaoInput,   /**< G-buffer framebuffer with position, normal, and albedo attachments. */
    Ssao,        /**< SSAO computation framebuffer with occlusion output. */
    SsaoBlur,    /**< SSAO blur framebuffer with smoothed occlusion output. */
    Default,     /**< Default framebuffer (screen) for final rendering. */
    Unknown      /**< Sentinel value for uninitialized or invalid framebuffer IDs. */
};

#endif
