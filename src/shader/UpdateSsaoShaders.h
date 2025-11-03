#ifndef UPDATE_SSAO_SHADERS_H
#define UPDATE_SSAO_SHADERS_H

struct GuiParameters;
struct GuiUpdateFlags;
class SsaoUtils;
class Shader;
class Texture;

namespace ShaderUtils
{
    void UpdateSsaoShaders(
        GuiUpdateFlags& guiUpdateFlags,
        const GuiParameters& guiParameters,
        SsaoUtils& ssaoUtils,
        Texture& ssaoNoiseTexture,
        const Shader& ssaoShader,
        const Shader& ssaoFinalShader
    );
}

#endif
