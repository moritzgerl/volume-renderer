#ifndef STORAGE_H
#define STORAGE_H

#include <storage/TextureStorage.h>
#include <storage/ShaderStorage.h>
#include <storage/FrameBufferStorage.h>
#include <storage/RenderPassStorage.h>

class Storage
{
public:
    explicit Storage(
        TextureStorage&& textureStorage,
        ShaderStorage&& shaderStorage,
        FrameBufferStorage&& frameBufferStorage,
        RenderPassStorage&& renderPassStorage);

    // TODO use concepts
    // TODO rule of zero? Don't even do the = delete here?
    // If we keep it, do the same in the other storage classes
    Storage(const Storage&) = delete;
    Storage& operator=(const Storage&) = delete;
    Storage(Storage&&) = delete;
    Storage& operator=(Storage&&) = delete;

    Texture const& GetTexture(TextureId textureId) const;
    Texture& GetTexture(TextureId textureId);
    Shader const& GetShader(ShaderId shaderId) const;
    const FrameBuffer& GetFrameBuffer(FrameBufferId frameBufferId) const;
    const RenderPass& GetRenderPass(RenderPassId renderPassId) const;

private:
    TextureStorage m_textureStorage;
    ShaderStorage m_shaderStorage;
    FrameBufferStorage m_frameBufferStorage;
    RenderPassStorage m_renderPassStorage;
};

#endif
