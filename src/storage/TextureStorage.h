#ifndef TEXTURE_STORAGE_H
#define TEXTURE_STORAGE_H

#include <textures/Texture.h>
#include <textures/TextureId.h>
#include <storage/ElementStorage.h>

class TextureStorage
{
public:
    TextureStorage(std::vector<Texture>&& textures);
    const Texture& GetTexture(TextureId textureId) const;
    Texture& GetTexture(TextureId textureId);

private:
    ElementStorage<Texture, TextureId> m_storage;
};

#endif
