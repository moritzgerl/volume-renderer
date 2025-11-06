#ifndef SSAO_UPDATER_H
#define SSAO_UPDATER_H

struct GuiParameters;
struct GuiUpdateFlags;
class SsaoUtils;
class Shader;
class Storage;
class Texture;

class SsaoUpdater
{
public:
    SsaoUpdater(Storage& storage);

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
