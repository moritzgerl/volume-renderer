/**
* \file TextureType.h
*
* \brief Enumeration of OpenGL texture dimensionalities.
*/

#ifndef TEXTURE_TYPE_H
#define TEXTURE_TYPE_H

/**
* \enum TextureType
*
* \brief Identifies the dimensionality of OpenGL textures.
*
* Specifies whether a texture is 1D, 2D, or 3D, which determines
* how it is created, sampled, and bound in OpenGL. Each type maps
* to a corresponding OpenGL texture target (GL_TEXTURE_1D, etc.).
*
* @see Texture for texture creation and management.
* @see TextureId for identifying specific texture instances.
*/
enum class TextureType
{
    Texture1D,  /**< 1D texture (e.g., transfer function lookup table). */
    Texture2D,  /**< 2D texture (e.g., SSAO output, G-buffer attachments). */
    Texture3D   /**< 3D texture (e.g., volume data). */
};

#endif
