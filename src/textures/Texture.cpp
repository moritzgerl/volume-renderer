#include <textures/Texture.h>
#include <textures/TextureUnitMapping.h>

#include <glad/glad.h>

#include <iostream>

namespace Constants
{
    const float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
}

Texture::Texture(TextureId textureId, GLenum textureUnit, unsigned int width, unsigned int height, GLenum internalFormat, GLenum format, GLenum type, GLenum filterParameter, GLenum wrapParameter)
    : m_textureId(textureId)
    , m_glTextureId()
    , m_textureUnitEnum(textureUnit)
    , m_textureUnitInt(TextureUnitMapping::GLenumToUnsignedInt(textureUnit))
{
    Create(width, height, internalFormat, format, type, filterParameter, wrapParameter, NULL);
}

Texture::Texture(TextureId textureId, GLenum textureUnit, unsigned int width, unsigned int height, GLenum internalFormat, GLenum format, GLenum type, GLenum filterParameter, GLenum wrapParameter, const void* data)
    : m_textureId(textureId)
    , m_glTextureId()
    , m_textureUnitEnum(textureUnit)
    , m_textureUnitInt(TextureUnitMapping::GLenumToUnsignedInt(textureUnit))
{
    Create(width, height, internalFormat, format, type, filterParameter, wrapParameter, data);
}

void Texture::Create(unsigned int width, unsigned int height, GLenum internalFormat, GLenum format, GLenum type, GLenum filterParameter, GLenum wrapParameter, const void* data)
{
    glGenTextures(1, &m_glTextureId);
    glBindTexture(GL_TEXTURE_2D, m_glTextureId);
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterParameter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterParameter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapParameter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapParameter);
}

void Texture::AddBorder()
{
    glBindTexture(GL_TEXTURE_2D, m_glTextureId);
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, Constants::borderColor);
}

TextureId Texture::GetId() const
{
    return m_textureId;
}

unsigned int Texture::GetGlId() const
{
    return m_glTextureId;
}

unsigned int Texture::GetTextureUnit() const
{
    return m_textureUnitInt;
}

unsigned int Texture::GetTextureUnitEnum() const
{
    return m_textureUnitEnum;
}

void Texture::Bind() const
{
    glActiveTexture(m_textureUnitEnum);
    glBindTexture(GL_TEXTURE_2D, m_glTextureId);
}
