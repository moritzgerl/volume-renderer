#include "Storage.h"

Storage::Storage(ShaderStorage&& shaderStorage, TextureStorage&& textureStorage)
    : m_shaderStorage(std::move(shaderStorage))
    , m_textureStorage(std::move(textureStorage))
{
}

Shader const& Storage::GetShader(ShaderId shaderId) const
{
    return m_shaderStorage.GetShader(shaderId);
}

Texture const& Storage::GetTexture(TextureId textureId) const
{
    return m_textureStorage.GetTexture(textureId);
}

Texture& Storage::GetTexture(TextureId textureId)
{
    return m_textureStorage.GetTexture(textureId);
}
