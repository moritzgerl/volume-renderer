#include <textures/UpdateSsaoNoiseTexture.h>
#include <textures/Texture.h>
#include <textures/TextureId.h>
#include <gui/GuiParameters.h>
#include <utils/SsaoUtils.h>

#include <glad/glad.h>

// TODO move to SsaoUpdater
void TextureUtils::UpdateSsaoNoiseTexture(const GuiParameters& guiParameters, const SsaoUtils& ssaoUtils, Texture& ssaoNoiseTexture)
{
    ssaoNoiseTexture = Texture(TextureId::SsaoNoise, ssaoNoiseTexture.GetTextureUnitEnum(), guiParameters.ssaoNoiseSize, guiParameters.ssaoNoiseSize, GL_RGBA32F, GL_RGB, GL_FLOAT, GL_NEAREST, GL_REPEAT, ssaoUtils.GetNoise());
}
