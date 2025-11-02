#ifndef UPDATE_SSAO_SHADER_H
#define UPDATE_SSAO_SHADER_H

struct GuiParameters;
class Shader;
class SsaoUtils;

namespace ShaderUtils
{
    void UpdateSsaoShader(const GuiParameters& guiParameters, const SsaoUtils& ssaoUtils, const Shader& ssaoShader);
}

#endif
