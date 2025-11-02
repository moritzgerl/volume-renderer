#include <shader/UpdateSsaoShader.h>
#include <shader/Shader.h>
#include <gui/GuiParameters.h>
#include <utils/SsaoUtils.h>

#include <string>

void ShaderUtils::UpdateSsaoShader(const GuiParameters& guiParameters, const SsaoUtils& ssaoUtils, const Shader& ssaoShader)
{
    ssaoShader.SetInt("kernelSize", guiParameters.ssaoKernelSize);
    ssaoShader.SetInt("noiseSize", guiParameters.ssaoNoiseSize);
    ssaoShader.SetFloat("radius", guiParameters.ssaoRadius);
    ssaoShader.SetFloat("bias", guiParameters.ssaoBias);

    for (unsigned int i = 0; i < guiParameters.ssaoKernelSize; ++i)
    {
        ssaoShader.SetVec3("samples[" + std::to_string(i) + "]", ssaoUtils.GetSamplePosition(i));
    }
}
