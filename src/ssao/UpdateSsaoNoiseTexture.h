#ifndef UPDATE_SSAO_NOISE_TEXTURE_H
#define UPDATE_SSAO_NOISE_TEXTURE_H

struct GuiParameters;
class SsaoUtils;
class Texture;

namespace TextureUtils
{
    void UpdateSsaoNoiseTexture(const GuiParameters& guiParameters, const SsaoUtils& ssaoUtils, Texture& ssaoNoiseTexture);
}

#endif
