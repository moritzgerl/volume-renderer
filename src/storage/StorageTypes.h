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

using TextureStorage = ElementStorage<Texture, TextureId>;
using ShaderStorage = ElementStorage<Shader, ShaderId>;
using FrameBufferStorage = ElementStorage<FrameBuffer, FrameBufferId>;
using RenderPassStorage = ElementStorage<RenderPass, RenderPassId>;

#endif
