#include <storage/TextureStorage.h>
#include <algorithm>
#include <iostream>

TextureStorage::TextureStorage(std::vector<Texture>&& textures)
    : m_textures(std::move(textures))
{
}

Texture const& TextureStorage::GetTexture(TextureId textureId) const
{
    auto textureIter = std::find_if(m_textures.begin(), m_textures.end(),
        [textureId]
        (const Texture& texture)
        {
            return texture.GetTextureId() == textureId;
        }
    );

    if (textureIter == m_textures.end())
    {
        std::cerr << "TextureStorage::GetTexture - could not find texture with the specified TextureId" << std::endl;
        return m_textures[0];
    }

    return *textureIter;
}
