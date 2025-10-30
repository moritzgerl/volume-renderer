#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

class Texture
{
public:
    Texture(unsigned int textureUnit, unsigned int width, unsigned int height, unsigned int internalFormat, unsigned int format, unsigned int type, unsigned int filterParameter, unsigned int wrapParameter);
    Texture(unsigned int textureUnit, unsigned int width, unsigned int height, unsigned int internalFormat, unsigned int format, unsigned int type, unsigned int filterParameter, unsigned int wrapParameter, const void* data);
    void AddBorder();
    unsigned int GetId() const;
    unsigned int GetTextureUnit() const;
    unsigned int GetTextureUnitEnum() const;
    void Bind() const;

private:
    void Create(unsigned int width, unsigned int height, unsigned int internalFormat, unsigned int format, unsigned int type, unsigned int filterParameter, unsigned int wrapParameter, const void* data);

private:
    unsigned int m_textureId;
    unsigned int m_textureUnitEnum;
    unsigned int m_textureUnitInt;
};

#endif