#ifndef SSAO_UPDATER_H
#define SSAO_UPDATER_H

struct GuiParameters;
struct GuiUpdateFlags;
class SsaoUtils;
class Shader;
class Texture;

class SsaoUpdater
{
public:
    SsaoUpdater(
        GuiUpdateFlags& guiUpdateFlags,
        const GuiParameters& guiParameters,
        SsaoUtils& ssaoUtils,
        Texture& ssaoNoiseTexture,
        const Shader& ssaoShader,
        const Shader& ssaoFinalShader
    );

    void Update();

private:
    GuiUpdateFlags& m_guiUpdateFlags;
    const GuiParameters& m_guiParameters;
    SsaoUtils& m_ssaoUtils;
    Texture& m_ssaoNoiseTexture;
    const Shader& m_ssaoShader;
    const Shader& m_ssaoFinalShader;
};

#endif
