#include <shader/UpdateSsaoShaders.h>
#include <shader/Shader.h>
#include <shader/UpdateSsaoShader.h>
#include <shader/UpdateSsaoFinalShader.h>
#include <textures/Texture.h>
#include <textures/UpdateSsaoNoiseTexture.h>
#include <gui/GuiParameters.h>
#include <gui/GuiUpdateFlags.h>
#include <utils/SsaoUtils.h>

namespace ShaderUtils
{
    void UpdateSsaoShaders(
        GuiUpdateFlags& guiUpdateFlags,
        const GuiParameters& guiParameters,
        SsaoUtils& ssaoUtils,
        Texture& ssaoNoiseTexture,
        const Shader& ssaoShader,
        const Shader& ssaoFinalShader
    )
    {
        if (guiUpdateFlags.ssaoParametersChanged)
        {
            ssaoUtils.UpdateKernel(guiParameters.ssaoKernelSize);
            ssaoUtils.UpdateNoise(guiParameters.ssaoNoiseSize);
            TextureUtils::UpdateSsaoNoiseTexture(guiParameters, ssaoUtils, ssaoNoiseTexture);
            ssaoShader.Use();
            ShaderUtils::UpdateSsaoShader(guiParameters, ssaoUtils, ssaoShader);
            ssaoFinalShader.Use();
            ShaderUtils::UpdateSsaoFinalShader(guiParameters, ssaoFinalShader);
            guiUpdateFlags.ssaoParametersChanged = false;
        }
    }
}
