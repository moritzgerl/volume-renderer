#ifndef SSAO_UPDATER_H
#define SSAO_UPDATER_H

struct GuiParameters;
struct GuiUpdateFlags;
class SsaoKernel;
class Shader;
class Texture;

class SsaoUpdater
{
public:
    SsaoUpdater(
        GuiUpdateFlags& guiUpdateFlags,
        const GuiParameters& guiParameters,
        SsaoKernel& ssaoKernel,
        Texture& ssaoNoiseTexture,
        const Shader& ssaoShader,
        const Shader& ssaoFinalShader
    );

    void Update();

private:
    void UpdateSsaoNoiseTexture();
    void UpdateSsaoShader();
    void UpdateSsaoFinalShader();

private:
    GuiUpdateFlags& m_guiUpdateFlags;
    const GuiParameters& m_guiParameters;
    SsaoKernel& m_ssaoKernel;
    Texture& m_ssaoNoiseTexture;
    const Shader& m_ssaoShader;
    const Shader& m_ssaoFinalShader;
};

#endif
