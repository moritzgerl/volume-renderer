#include <storage/Storage.h>

Storage::Storage(TextureStorage&& textureStorage, ShaderStorage&& shaderStorage, FrameBufferStorage&& frameBufferStorage)
    : m_textureStorage(std::move(textureStorage))
    , m_shaderStorage(std::move(shaderStorage))
    , m_frameBufferStorage(std::move(frameBufferStorage))
{
}

Texture const& Storage::GetTexture(TextureId textureId) const
{
    return m_textureStorage.GetTexture(textureId);
}

Texture& Storage::GetTexture(TextureId textureId)
{
    return m_textureStorage.GetTexture(textureId);
}

Shader const& Storage::GetShader(ShaderId shaderId) const
{
    return m_shaderStorage.GetShader(shaderId);
}

const FrameBuffer& Storage::GetFrameBuffer(FrameBufferId frameBufferId) const
{
    return m_frameBufferStorage.GetFrameBuffer(frameBufferId);
}
