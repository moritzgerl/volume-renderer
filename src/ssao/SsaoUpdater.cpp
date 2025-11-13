#include <ssao/SsaoUpdater.h>

#include <gui/GuiParameters.h>
#include <gui/GuiUpdateFlags.h>
#include <shader/Shader.h>
#include <ssao/SsaoKernel.h>
#include <textures/Texture.h>
#include <textures/TextureId.h>

#include <glad/glad.h>
#include <string>

SsaoUpdater::SsaoUpdater(
    GuiUpdateFlags& guiUpdateFlags,
    const GuiParameters& guiParameters,
    SsaoKernel& ssaoKernel,
    Texture& ssaoNoiseTexture,
    const Shader& ssaoShader,
    const Shader& ssaoFinalShader
)
    : m_guiUpdateFlags(guiUpdateFlags)
    , m_guiParameters(guiParameters)
    , m_ssaoKernel(ssaoKernel)
    , m_ssaoNoiseTexture(ssaoNoiseTexture)
    , m_ssaoShader(ssaoShader)
    , m_ssaoFinalShader(ssaoFinalShader)
{
}

void SsaoUpdater::Update()
{
    if (m_guiUpdateFlags.ssaoParametersChanged)
    {
        m_ssaoKernel.UpdateKernel(m_guiParameters.ssaoKernelSize);
        m_ssaoKernel.UpdateNoise(m_guiParameters.ssaoNoiseSize);
        UpdateSsaoNoiseTexture();
        m_ssaoShader.Use();
        UpdateSsaoShader();
        m_ssaoFinalShader.Use();
        UpdateSsaoFinalShader();
        m_guiUpdateFlags.ssaoParametersChanged = false;
    }
}

void SsaoUpdater::UpdateSsaoNoiseTexture()
{
    m_ssaoNoiseTexture = Texture(
        TextureId::SsaoNoise,
        m_ssaoNoiseTexture.GetTextureUnitEnum(),
        m_guiParameters.ssaoNoiseSize,
        m_guiParameters.ssaoNoiseSize,
        GL_RGBA32F,
        GL_RGB,
        GL_FLOAT,
        GL_NEAREST,
        GL_REPEAT,
        m_ssaoKernel.GetNoise()
    );
}

void SsaoUpdater::UpdateSsaoShader()
{
    m_ssaoShader.SetInt("kernelSize", m_guiParameters.ssaoKernelSize);
    m_ssaoShader.SetInt("noiseSize", m_guiParameters.ssaoNoiseSize);
    m_ssaoShader.SetFloat("radius", m_guiParameters.ssaoRadius);
    m_ssaoShader.SetFloat("bias", m_guiParameters.ssaoBias);

    for (unsigned int i = 0; i < m_guiParameters.ssaoKernelSize; ++i)
    {
        m_ssaoShader.SetVec3("samples[" + std::to_string(i) + "]", m_ssaoKernel.GetSamplePosition(i));
    }
}

void SsaoUpdater::UpdateSsaoFinalShader()
{
    m_ssaoFinalShader.SetInt("enableSsao", static_cast<int>(m_guiParameters.enableSsao));
}
