#ifndef MAKE_TEXTURES_H
#define MAKE_TEXTURES_H

#include <textures/Texture.h>
#include <vector>

class SsaoUtils;

namespace Factory
{
    std::vector<Texture> MakeTextures(const SsaoUtils& ssaoUtils);
}

#endif
