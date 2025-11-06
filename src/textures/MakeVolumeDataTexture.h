#ifndef MAKE_VOLUME_DATA_TEXTURE_H
#define MAKE_VOLUME_DATA_TEXTURE_H

#include <textures/Texture.h>
#include <textures/TextureId.h>

namespace Data
{
    class VolumeData;
}

namespace Factory
{
    Texture MakeVolumeDataTexture(TextureId textureId, unsigned int textureUnit, const Data::VolumeData& volumeData);
}

#endif
