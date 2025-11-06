#include <shader/SsaoUpdater.h>
#include <shader/Shader.h>
#include <shader/UpdateSsaoFinalShader.h>
#include <shader/UpdateSsaoShader.h>
#include <gui/GuiParameters.h>
#include <gui/GuiUpdateFlags.h>
#include <textures/Texture.h>
#include <textures/UpdateSsaoNoiseTexture.h>
#include <utils/SsaoUtils.h>

SsaoUpdater::SsaoUpdater(
    GuiUpdateFlags& guiUpdateFlags,
    const GuiParameters& guiParameters,
    SsaoUtils& ssaoUtils,
    Texture& ssaoNoiseTexture,
    const Shader& ssaoShader,
    const Shader& ssaoFinalShader
)
    : m_guiUpdateFlags(guiUpdateFlags)
    , m_guiParameters(guiParameters)
    , m_ssaoUtils(ssaoUtils)
    , m_ssaoNoiseTexture(ssaoNoiseTexture)
    , m_ssaoShader(ssaoShader)
    , m_ssaoFinalShader(ssaoFinalShader)
{
}

void SsaoUpdater::Update()
{
    if (m_guiUpdateFlags.ssaoParametersChanged)
    {
        m_ssaoUtils.UpdateKernel(m_guiParameters.ssaoKernelSize);
        m_ssaoUtils.UpdateNoise(m_guiParameters.ssaoNoiseSize);
        TextureUtils::UpdateSsaoNoiseTexture(m_guiParameters, m_ssaoUtils, m_ssaoNoiseTexture);
        m_ssaoShader.Use();
        ShaderUtils::UpdateSsaoShader(m_guiParameters, m_ssaoUtils, m_ssaoShader);
        m_ssaoFinalShader.Use();
        ShaderUtils::UpdateSsaoFinalShader(m_guiParameters, m_ssaoFinalShader);
        m_guiUpdateFlags.ssaoParametersChanged = false;
    }
}
