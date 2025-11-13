#ifndef MAKE_TEXTURES_H
#define MAKE_TEXTURES_H

#include <textures/Texture.h>
#include <vector>

namespace VolumeData
{
    class VolumeData;
}

struct GuiParameters;
class SsaoKernel;

namespace Factory
{
    std::vector<Texture> MakeTextures(const GuiParameters& guiParameters, const VolumeData::VolumeData& volumeData, const SsaoKernel& ssaoKernel);
}

#endif
