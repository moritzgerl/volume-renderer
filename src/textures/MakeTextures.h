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
    std::vector<Texture> MakeTextures(const VolumeData::VolumeData& volumeData, const SsaoKernel& ssaoKernel);
}

#endif
