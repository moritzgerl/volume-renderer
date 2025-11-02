#include <shader/UpdateLightingParametersInShader.h>
#include <shader/Shader.h>
#include <config/Config.h>
#include <gui/GuiParameters.h>

#include <string>

void ShaderUtils::UpdateLightingParametersInShader(const GuiParameters& guiParameters, const Shader& shader)
{
    shader.SetVec3("directionalLight.direction", guiParameters.directionalLight.direction);
    shader.SetVec3("directionalLight.ambient", guiParameters.directionalLight.ambient);
    shader.SetVec3("directionalLight.diffuse", guiParameters.directionalLight.diffuse);
    shader.SetVec3("directionalLight.specular", guiParameters.directionalLight.specular);
    shader.SetFloat("directionalLight.intensity", guiParameters.directionalLight.intensity);

    for (unsigned int i = 0; i < Config::numPointLights; ++i)
    {
        const std::string name = "pointLights[" + std::to_string(i) + "]";

        shader.SetVec3(name + ".position", guiParameters.pointLights[i].position);
        shader.SetVec3(name + ".ambient", guiParameters.pointLights[i].ambient);
        shader.SetVec3(name + ".diffuse", guiParameters.pointLights[i].diffuse);
        shader.SetVec3(name + ".specular", guiParameters.pointLights[i].specular);
        shader.SetFloat(name + ".intensity", guiParameters.pointLights[i].intensity);
    }

    shader.SetVec3("material.specular", 1.0f, 1.0f, 1.0f);
    shader.SetFloat("material.shininess", 1.0f);
}
