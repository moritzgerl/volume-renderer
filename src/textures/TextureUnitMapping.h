/**
* \file TextureUnitMapping.h
*
* \brief Texture unit mapping utilities for OpenGL texture binding.
*/

#ifndef TEXTURE_UNIT_MAPPING_H
#define TEXTURE_UNIT_MAPPING_H

/**
* \namespace TextureUnitMapping
*
* \brief Utilities for converting OpenGL texture unit enums to indices.
*
* Provides helper functions for working with OpenGL texture unit identifiers,
* converting between GL_TEXTURE0-based enums and zero-based unsigned integers
* for array indexing and shader uniform setting.
*
* @see Texture for texture creation and binding.
* @see Shader for setting texture sampler uniforms.
*/
namespace TextureUnitMapping
{
    /**
    * Converts an OpenGL texture unit enum to a zero-based unsigned integer.
    * @param textureUnit OpenGL texture unit (e.g., GL_TEXTURE0, GL_TEXTURE1).
    * @return Zero-based texture unit index (e.g., 0 for GL_TEXTURE0, 1 for GL_TEXTURE1).
    */
    unsigned int GLenumToUnsignedInt(unsigned int textureUnit);
}

#endif
