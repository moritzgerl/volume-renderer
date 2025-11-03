#include <storage/TextureStorage.h>
#include <algorithm>
#include <iostream>

namespace
{
    template <typename T>
    auto& GetTextureImpl(TextureId textureId, T& textures)
    {
        auto textureIter = std::find_if(textures.begin(), textures.end(),
            [textureId]
            (const Texture& texture)
        {
            return texture.GetTextureId() == textureId;
        }
        );

        if (textureIter == textures.end())
        {
            std::cerr << "TextureStorage::GetTexture - could not find texture with the specified TextureId" << std::endl;
            return textures[0];
        }

        return *textureIter;
    }
}

TextureStorage::TextureStorage(std::vector<Texture>&& textures)
    : m_textures(std::move(textures))
{
}

const Texture& TextureStorage::GetTexture(TextureId textureId) const
{
    return GetTextureImpl(textureId, m_textures);
}

Texture& TextureStorage::GetTexture(TextureId textureId)
{
    return GetTextureImpl(textureId, m_textures);
}
