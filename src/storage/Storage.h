#ifndef STORAGE_H
#define STORAGE_H

#include <storage/ElementStorage.h>
#include <textures/Texture.h>
#include <textures/TextureId.h>
#include <shader/Shader.h>
#include <shader/ShaderId.h>
#include <buffers/FrameBuffer.h>
#include <buffers/FrameBufferId.h>
#include <renderpass/RenderPass.h>
#include <renderpass/RenderPassId.h>

class Storage
{
public:
    explicit Storage(
        ElementStorage<Texture, TextureId>&& textureStorage,
        ElementStorage<Shader, ShaderId>&& shaderStorage,
        ElementStorage<FrameBuffer, FrameBufferId>&& frameBufferStorage,
        ElementStorage<RenderPass, RenderPassId>&& renderPassStorage);

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
    ElementStorage<Texture, TextureId> m_textureStorage;
    ElementStorage<Shader, ShaderId> m_shaderStorage;
    ElementStorage<FrameBuffer, FrameBufferId> m_frameBufferStorage;
    ElementStorage<RenderPass, RenderPassId> m_renderPassStorage;
};

#endif
