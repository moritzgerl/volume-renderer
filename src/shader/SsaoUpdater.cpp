#include <shader/SsaoUpdater.h>
#include <shader/Shader.h>
#include <shader/ShaderId.h>
#include <shader/UpdateSsaoFinalShader.h>
#include <shader/UpdateSsaoShader.h>
#include <storage/Storage.h>
#include <textures/Texture.h>
#include <textures/TextureId.h>
#include <textures/UpdateSsaoNoiseTexture.h>
#include <gui/GuiParameters.h>
#include <gui/GuiUpdateFlags.h>
#include <utils/SsaoUtils.h>

SsaoUpdater::SsaoUpdater(Storage& storage)
    : m_guiUpdateFlags(storage.GetGuiUpdateFlags())
    , m_guiParameters(storage.GetGuiParameters())
    , m_ssaoUtils(storage.GetSsaoUtils())
    , m_ssaoNoiseTexture(storage.GetTexture(TextureId::SsaoNoise))
    , m_ssaoShader(storage.GetShader(ShaderId::Ssao))
    , m_ssaoFinalShader(storage.GetShader(ShaderId::SsaoFinal))
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
