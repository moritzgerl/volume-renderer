/**
* \file UpdateLightingParametersInShader.h
*
* \brief Utility for updating lighting parameters in shaders.
*/

#ifndef UPDATE_LIGHTING_PARAMETERS_IN_SHADER_H
#define UPDATE_LIGHTING_PARAMETERS_IN_SHADER_H

struct GuiParameters;
class Shader;

namespace ShaderUtils
{
    /**
    * Updates lighting-related uniforms in a shader program.
    *
    * Sets directional light and point light uniforms in the shader based
    * on the current GUI parameters. This includes light positions, colors,
    * ambient/diffuse/specular components, and attenuation parameters.
    *
    * This function should be called before rendering any pass that requires
    * lighting calculations (volume rendering, SSAO final composition, etc.).
    *
    * @param guiParameters The GUI parameters containing light configurations.
    * @param shader The shader to update with lighting parameters.
    * @return void
    *
    * @see GuiParameters for light parameter storage.
    * @see DirectionalLight for directional light structure.
    * @see PointLight for point light structure.
    * @see Shader for shader uniform management.
    */
    void UpdateLightingParametersInShader(const GuiParameters& guiParameters, const Shader& shader);
}

#endif
