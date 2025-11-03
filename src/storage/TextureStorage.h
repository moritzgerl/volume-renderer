#ifndef TEXTURE_STORAGE_H
#define TEXTURE_STORAGE_H

#include <textures/Texture.h>
#include <textures/TextureId.h>
#include <vector>

class TextureStorage
{
public:
    TextureStorage(std::vector<Texture>&& textures);
    Texture const& GetTexture(TextureId textureId) const;

private:
    std::vector<Texture> m_textures;
};

#endif
