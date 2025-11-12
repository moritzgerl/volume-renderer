#ifndef TEXTURE_H
#define TEXTURE_H

#include <textures/TextureId.h>
#include <textures/TextureType.h>
#include <string>

class Texture
{
public:
    Texture(TextureId textureId, unsigned int textureUnit, unsigned int width, unsigned int internalFormat, unsigned int format, unsigned int type, unsigned int filterParameter, unsigned int wrapParameter);
    Texture(TextureId textureId, unsigned int textureUnit, unsigned int width, unsigned int height, unsigned int internalFormat, unsigned int format, unsigned int type, unsigned int filterParameter, unsigned int wrapParameter);
    Texture(TextureId textureId, unsigned int textureUnit, unsigned int width, unsigned int height, unsigned int internalFormat, unsigned int format, unsigned int type, unsigned int filterParameter, unsigned int wrapParameter, const void* data);
    Texture(TextureId textureId, unsigned int textureUnit, unsigned int width, unsigned int height, unsigned int depth, unsigned int internalFormat, unsigned int format, unsigned int type, unsigned int filterParameter, unsigned int wrapParameter, const void* data);
    void AddBorder();
    unsigned int GetGlId() const;
    unsigned int GetTextureUnit() const;
    unsigned int GetTextureUnitEnum() const;
    TextureId GetId() const;
    TextureType GetTextureType() const;
    void Bind() const;

private:
    void Create1D(unsigned int width, unsigned int internalFormat, unsigned int format, unsigned int type, unsigned int filterParameter, unsigned int wrapParameter, const void* data);
    void Create2D(unsigned int width, unsigned int height, unsigned int internalFormat, unsigned int format, unsigned int type, unsigned int filterParameter, unsigned int wrapParameter, const void* data);
    void Create3D(unsigned int width, unsigned int height, unsigned int depth, unsigned int internalFormat, unsigned int format, unsigned int type, unsigned int filterParameter, unsigned int wrapParameter, const void* data);

private:
    TextureId m_textureId;
    TextureType m_textureType;
    unsigned int m_glTextureId;
    unsigned int m_textureUnitEnum;
    unsigned int m_textureUnitInt;
};

#endif
