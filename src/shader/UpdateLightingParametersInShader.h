#ifndef UPDATE_LIGHTING_PARAMETERS_IN_SHADER_H
#define UPDATE_LIGHTING_PARAMETERS_IN_SHADER_H

struct GuiParameters;
class Shader;

namespace ShaderUtils
{
    void UpdateLightingParametersInShader(const GuiParameters& guiParameters, Shader& shader);
}

#endif
