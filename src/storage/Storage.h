#ifndef STORAGE_H
#define STORAGE_H

#include <storage/StorageTypes.h>
#include <vector>

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

    // TODO remove unused getters
    Texture const& GetTexture(TextureId textureId) const;
    Texture& GetTexture(TextureId textureId);
    Shader const& GetShader(ShaderId shaderId) const;
    const FrameBuffer& GetFrameBuffer(FrameBufferId frameBufferId) const;
    const RenderPass& GetRenderPass(RenderPassId renderPassId) const;
    const std::vector<RenderPass>& GetRenderPasses() const;

private:
    TextureStorage m_textureStorage;
    ShaderStorage m_shaderStorage;
    FrameBufferStorage m_frameBufferStorage;
    RenderPassStorage m_renderPassStorage;
};

#endif
