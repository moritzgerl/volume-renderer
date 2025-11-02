#include <shader/UpdateSsaoShader.h>
#include <shader/Shader.h>
#include <gui/GuiParameters.h>
#include <utils/SsaoUtils.h>

#include <string>

void ShaderUtils::UpdateSsaoShader(const GuiParameters& guiParameters, const SsaoUtils& ssaoUtils, const Shader& ssaoShader)
{
    ssaoShader.setInt("kernelSize", guiParameters.ssaoKernelSize);
    ssaoShader.setInt("noiseSize", guiParameters.ssaoNoiseSize);
    ssaoShader.setFloat("radius", guiParameters.ssaoRadius);
    ssaoShader.setFloat("bias", guiParameters.ssaoBias);

    for (unsigned int i = 0; i < guiParameters.ssaoKernelSize; ++i)
    {
        ssaoShader.setVec3("samples[" + std::to_string(i) + "]", ssaoUtils.GetSamplePosition(i));
    }
}
