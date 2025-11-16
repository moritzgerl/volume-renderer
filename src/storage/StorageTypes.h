/**
* \file StorageTypes.h
*
* \brief Type aliases for resource storage containers.
*/

#ifndef STORAGE_TYPES_H
#define STORAGE_TYPES_H

#include <storage/ElementStorage.h>
#include <textures/Texture.h>
#include <textures/TextureId.h>
#include <shader/Shader.h>
#include <shader/ShaderId.h>
#include <buffers/FrameBuffer.h>
#include <buffers/FrameBufferId.h>
#include <renderpass/RenderPass.h>
#include <renderpass/RenderPassId.h>

/**
* \typedef TextureStorage
*
* \brief Storage container for textures indexed by TextureId.
*
* Type alias for ElementStorage specialized for Texture objects.
* Allows type-safe retrieval of textures by TextureId enum.
*
* @see ElementStorage for the generic storage template.
* @see Texture for texture objects.
* @see TextureId for texture identifiers.
*/
using TextureStorage = ElementStorage<Texture, TextureId>;

/**
* \typedef ShaderStorage
*
* \brief Storage container for shaders indexed by ShaderId.
*
* Type alias for ElementStorage specialized for Shader objects.
* Allows type-safe retrieval of shaders by ShaderId enum.
*
* @see ElementStorage for the generic storage template.
* @see Shader for shader objects.
* @see ShaderId for shader identifiers.
*/
using ShaderStorage = ElementStorage<Shader, ShaderId>;

/**
* \typedef FrameBufferStorage
*
* \brief Storage container for framebuffers indexed by FrameBufferId.
*
* Type alias for ElementStorage specialized for FrameBuffer objects.
* Allows type-safe retrieval of framebuffers by FrameBufferId enum.
*
* @see ElementStorage for the generic storage template.
* @see FrameBuffer for framebuffer objects.
* @see FrameBufferId for framebuffer identifiers.
*/
using FrameBufferStorage = ElementStorage<FrameBuffer, FrameBufferId>;

/**
* \typedef RenderPassStorage
*
* \brief Storage container for render passes indexed by RenderPassId.
*
* Type alias for ElementStorage specialized for RenderPass objects.
* Allows type-safe retrieval of render passes by RenderPassId enum.
*
* @see ElementStorage for the generic storage template.
* @see RenderPass for render pass objects.
* @see RenderPassId for render pass identifiers.
*/
using RenderPassStorage = ElementStorage<RenderPass, RenderPassId>;

#endif
