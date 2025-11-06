#ifndef MAKE_TEXTURES_H
#define MAKE_TEXTURES_H

#include <textures/Texture.h>
#include <vector>

namespace Data
{
    class VolumeData;
}

class SsaoUtils;

namespace Factory
{
    std::vector<Texture> MakeTextures(const Data::VolumeData& volumeData, const SsaoUtils& ssaoUtils);
}

#endif
