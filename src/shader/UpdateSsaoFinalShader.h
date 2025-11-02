#ifndef UPDATE_SSAO_FINAL_SHADER_H
#define UPDATE_SSAO_FINAL_SHADER_H

struct GuiParameters;
class Shader;

namespace ShaderUtils
{
    void UpdateSsaoFinalShader(const GuiParameters& guiParameters, const Shader& ssaoFinalShader);
}

#endif
