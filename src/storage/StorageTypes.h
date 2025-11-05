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

typedef ElementStorage<Texture, TextureId> TextureStorage;
typedef ElementStorage<Shader, ShaderId> ShaderStorage;
typedef ElementStorage<FrameBuffer, FrameBufferId> FrameBufferStorage;
typedef ElementStorage<RenderPass, RenderPassId> RenderPassStorage;

#endif
