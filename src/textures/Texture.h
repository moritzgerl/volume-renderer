/**
* \file Texture.h
*
* \brief Texture creation and management for OpenGL textures.
*/

#ifndef TEXTURE_H
#define TEXTURE_H

#include <textures/TextureId.h>
#include <textures/TextureType.h>
#include <string>

/**
* \class Texture
*
* \brief Encapsulates OpenGL texture creation, binding, and management.
*
* Supports creation of 1D, 2D, and 3D textures with various internal formats, filtering,
* and wrapping modes. Each texture is bound to a specific texture unit and identified
* by a TextureId for type-safe retrieval from Storage.
*
* Textures are created via Factory::MakeTextures() which configures all textures needed
* for the rendering pipeline including volume data textures, transfer function textures,
* framebuffer attachments, and SSAO noise textures.
*
* @see TextureId for the enumeration of texture types.
* @see TextureType for distinguishing 1D, 2D, and 3D textures.
* @see Factory::MakeTextures for construction of all textures.
* @see TextureUnitMapping for named texture unit assignments.
* @see RenderPass for binding textures during rendering.
*/
class Texture
{
public:
    /**
    * Constructor for 1D textures with initial data.
    * @param textureId The ID identifying this texture.
    * @param textureUnit The texture unit to bind to (e.g., 0 for GL_TEXTURE0).
    * @param width The width of the texture in pixels.
    * @param internalFormat The internal format (e.g., GL_RGB, GL_R16).
    * @param format The format of the data (e.g., GL_RGB, GL_RED).
    * @param type The data type (e.g., GL_UNSIGNED_BYTE, GL_FLOAT).
    * @param filterParameter The minification/magnification filter (e.g., GL_LINEAR, GL_NEAREST).
    * @param wrapParameter The texture wrapping mode (e.g., GL_CLAMP_TO_EDGE, GL_REPEAT).
    * @param data Pointer to the initial texture data.
    */
    Texture(TextureId textureId, unsigned int textureUnit, unsigned int width, unsigned int internalFormat, unsigned int format, unsigned int type, unsigned int filterParameter, unsigned int wrapParameter, const void* data);

    /**
    * Constructor for 2D textures without initial data.
    */
    Texture(TextureId textureId, unsigned int textureUnit, unsigned int width, unsigned int height, unsigned int internalFormat, unsigned int format, unsigned int type, unsigned int filterParameter, unsigned int wrapParameter);

    /**
    * Constructor for 2D textures with initial data.
    */
    Texture(TextureId textureId, unsigned int textureUnit, unsigned int width, unsigned int height, unsigned int internalFormat, unsigned int format, unsigned int type, unsigned int filterParameter, unsigned int wrapParameter, const void* data);

    /**
    * Constructor for 3D textures with initial data.
    */
    Texture(TextureId textureId, unsigned int textureUnit, unsigned int width, unsigned int height, unsigned int depth, unsigned int internalFormat, unsigned int format, unsigned int type, unsigned int filterParameter, unsigned int wrapParameter, const void* data);

    ~Texture();
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;
    Texture(Texture&&) noexcept;
    Texture& operator=(Texture&&) noexcept;

    /**
    * Adds a border to the texture for border color sampling.
    * @return void
    */
    void AddBorder();

    unsigned int GetGlId() const;
    unsigned int GetTextureUnit() const;
    unsigned int GetTextureUnitEnum() const;
    TextureId GetId() const;
    TextureType GetTextureType() const;

    /**
    * Binds this texture to its assigned texture unit.
    * @return void
    */
    void Bind() const;

private:
    /**
    * Creates a 1D OpenGL texture.
    */
    void Create1D(unsigned int width, unsigned int internalFormat, unsigned int format, unsigned int type, unsigned int filterParameter, unsigned int wrapParameter, const void* data);

    /**
    * Creates a 2D OpenGL texture.
    */
    void Create2D(unsigned int width, unsigned int height, unsigned int internalFormat, unsigned int format, unsigned int type, unsigned int filterParameter, unsigned int wrapParameter, const void* data);

    /**
    * Creates a 3D OpenGL texture.
    */
    void Create3D(unsigned int width, unsigned int height, unsigned int depth, unsigned int internalFormat, unsigned int format, unsigned int type, unsigned int filterParameter, unsigned int wrapParameter, const void* data);

private:
    TextureId m_textureId; /**< The ID of this texture for identification. */
    TextureType m_textureType; /**< The texture type (1D, 2D, or 3D). */
    unsigned int m_glTextureId; /**< The OpenGL texture object handle. */
    unsigned int m_textureUnitEnum; /**< The GL_TEXTURE# enumeration value. */
    unsigned int m_textureUnitInt; /**< The texture unit as an integer (e.g., 0 for GL_TEXTURE0). */
};

#endif
