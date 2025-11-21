#include <textures/Texture.h>
#include <textures/TextureUnitMapping.h>

#include <glad/glad.h>

#include <iostream>

namespace Constants
{
    const float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
}

Texture::Texture(TextureId textureId, GLenum textureUnit, unsigned int width, GLenum internalFormat, GLenum format, GLenum type, GLenum filterParameter, GLenum wrapParameter, const void* data)
    : m_textureId{textureId}
    , m_textureType{TextureType::Texture1D}
    , m_glTextureId{}
    , m_textureUnitEnum{textureUnit}
    , m_textureUnitInt{TextureUnitMapping::GLenumToUnsignedInt(textureUnit)}
{
    Create1D(width, internalFormat, format, type, filterParameter, wrapParameter, data);
}

Texture::Texture(TextureId textureId, GLenum textureUnit, unsigned int width, unsigned int height, GLenum internalFormat, GLenum format, GLenum type, GLenum filterParameter, GLenum wrapParameter)
    : m_textureId{textureId}
    , m_textureType{TextureType::Texture2D}
    , m_glTextureId{}
    , m_textureUnitEnum{textureUnit}
    , m_textureUnitInt{TextureUnitMapping::GLenumToUnsignedInt(textureUnit)}
{
    Create2D(width, height, internalFormat, format, type, filterParameter, wrapParameter, NULL);
}

Texture::Texture(TextureId textureId, GLenum textureUnit, unsigned int width, unsigned int height, GLenum internalFormat, GLenum format, GLenum type, GLenum filterParameter, GLenum wrapParameter, const void* data)
    : m_textureId{textureId}
    , m_textureType{TextureType::Texture2D}
    , m_glTextureId{}
    , m_textureUnitEnum{textureUnit}
    , m_textureUnitInt{TextureUnitMapping::GLenumToUnsignedInt(textureUnit)}
{
    Create2D(width, height, internalFormat, format, type, filterParameter, wrapParameter, data);
}

Texture::Texture(TextureId textureId, GLenum textureUnit, unsigned int width, unsigned int height, unsigned int depth, GLenum internalFormat, GLenum format, GLenum type, GLenum filterParameter, GLenum wrapParameter, const void* data)
    : m_textureId{textureId}
    , m_textureType{TextureType::Texture3D}
    , m_glTextureId{}
    , m_textureUnitEnum{textureUnit}
    , m_textureUnitInt{TextureUnitMapping::GLenumToUnsignedInt(textureUnit)}
{
    Create3D(width, height, depth, internalFormat, format, type, filterParameter, wrapParameter, data);
}

void Texture::Create1D(unsigned int width, GLenum internalFormat, GLenum format, GLenum type, GLenum filterParameter, GLenum wrapParameter, const void* data)
{
    glGenTextures(1, &m_glTextureId);
    glBindTexture(GL_TEXTURE_1D, m_glTextureId);
    glTexImage1D(GL_TEXTURE_1D, 0, internalFormat, width, 0, format, type, data);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, filterParameter);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, filterParameter);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, wrapParameter);
}

void Texture::Create2D(unsigned int width, unsigned int height, GLenum internalFormat, GLenum format, GLenum type, GLenum filterParameter, GLenum wrapParameter, const void* data)
{
    glGenTextures(1, &m_glTextureId);
    glBindTexture(GL_TEXTURE_2D, m_glTextureId);
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterParameter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterParameter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapParameter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapParameter);
}

void Texture::Create3D(unsigned int width, unsigned int height, unsigned int depth, GLenum internalFormat, GLenum format, GLenum type, GLenum filterParameter, GLenum wrapParameter, const void* data)
{
    glGenTextures(1, &m_glTextureId);
    glBindTexture(GL_TEXTURE_3D, m_glTextureId);
    glTexImage3D(GL_TEXTURE_3D, 0, internalFormat, width, height, depth, 0, format, type, data);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, filterParameter);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, filterParameter);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, wrapParameter);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, wrapParameter);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, wrapParameter);
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

TextureType Texture::GetTextureType() const
{
    return m_textureType;
}

void Texture::Bind() const
{
    glActiveTexture(m_textureUnitEnum);

    switch (m_textureType)
    {
        case TextureType::Texture1D:
            glBindTexture(GL_TEXTURE_1D, m_glTextureId);
            break;
        case TextureType::Texture2D:
            glBindTexture(GL_TEXTURE_2D, m_glTextureId);
            break;
        case TextureType::Texture3D:
            glBindTexture(GL_TEXTURE_3D, m_glTextureId);
            break;
    }
}
