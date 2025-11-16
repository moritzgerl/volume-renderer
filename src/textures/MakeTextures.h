/**
* \file MakeTextures.h
*
* \brief Factory function for creating all textures used in the rendering pipeline.
*/

#ifndef MAKE_TEXTURES_H
#define MAKE_TEXTURES_H

#include <textures/Texture.h>
#include <vector>

namespace VolumeData
{
    class VolumeData;
}

class SsaoKernel;

namespace Factory
{
    /**
    * Creates and configures all textures for the rendering pipeline.
    *
    * Constructs texture objects for volume rendering, transfer function lookup,
    * SSAO computation (G-buffer textures for position, normal, albedo), SSAO
    * results, SSAO blur output, SSAO noise pattern, and point light contributions.
    * The volume data texture is created from the provided volume data, and the
    * SSAO noise texture is generated from the SSAO kernel. All textures are
    * configured with appropriate formats and dimensions. The textures are
    * indexed by TextureId enum values.
    *
    * @param volumeData Volume data to create the 3D volume texture from.
    * @param ssaoKernel SSAO kernel used to generate the noise texture.
    * @return Vector of configured Texture objects indexed by TextureId.
    *
    * @see Texture for texture object abstraction.
    * @see TextureId for texture identifier enumeration.
    * @see VolumeData for volume data storage.
    * @see SsaoKernel for SSAO sample generation.
    */
    std::vector<Texture> MakeTextures(const VolumeData::VolumeData& volumeData, const SsaoKernel& ssaoKernel);
}

#endif
