/**
* \file MakeVolumeDataTexture.h
*
* \brief Factory function for creating 3D volume data textures.
*/

#ifndef MAKE_VOLUME_DATA_TEXTURE_H
#define MAKE_VOLUME_DATA_TEXTURE_H

#include <textures/Texture.h>
#include <textures/TextureId.h>

namespace VolumeData
{
    class VolumeData;
}

namespace Factory
{
    /**
    * Creates a 3D OpenGL texture from volume data.
    *
    * Uploads the volume's voxel data to the GPU as a 3D texture for
    * volume ray-casting. Determines the internal format (R8 or R16)
    * based on the volume's bits per component.
    *
    * The texture is configured with linear filtering and clamp-to-edge
    * wrapping for proper volume rendering.
    *
    * @param textureId The identifier for this texture in Storage.
    * @param textureUnit The OpenGL texture unit to bind to (e.g., GL_TEXTURE0).
    * @param volumeData The volume data containing voxels and metadata.
    * @return Texture object configured as a 3D texture with the volume data.
    *
    * @see VolumeData for the volume data structure.
    * @see Texture for texture management.
    * @see TextureId for texture identifiers.
    */
    Texture MakeVolumeDataTexture(TextureId textureId, unsigned int textureUnit, const VolumeData::VolumeData& volumeData);
}

#endif
