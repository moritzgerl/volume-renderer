#ifndef STORAGE_H
#define STORAGE_H

#include <storage/ShaderStorage.h>
#include <storage/TextureStorage.h>

class Storage
{
public:
    explicit Storage(ShaderStorage&& shaderStorage, TextureStorage&& textureStorage);

    // TODO use concepts
    // TODO rule of zero? Don't even do the = delete here?
    // If we keep it, do the same in the other storage classes
    Storage(const Storage&) = delete;
    Storage& operator=(const Storage&) = delete;
    Storage(Storage&&) = delete;
    Storage& operator=(Storage&&) = delete;

    Shader const& GetShader(ShaderId shaderId) const;
    Texture const& GetTexture(TextureId textureId) const;

private:
    ShaderStorage m_shaderStorage;
    TextureStorage m_textureStorage;
};

#endif
