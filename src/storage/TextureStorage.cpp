#include <storage/TextureStorage.h>

TextureStorage::TextureStorage(std::vector<Texture>&& textures)
    : m_storage(std::move(textures))
{
}

const Texture& TextureStorage::GetTexture(TextureId textureId) const
{
    return m_storage.GetElement(textureId);
}

Texture& TextureStorage::GetTexture(TextureId textureId)
{
    return m_storage.GetElement(textureId);
}
