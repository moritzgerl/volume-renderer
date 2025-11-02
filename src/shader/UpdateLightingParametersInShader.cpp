#include <shader/UpdateLightingParametersInShader.h>
#include <shader/Shader.h>
#include <config/Config.h>
#include <gui/GuiParameters.h>

#include <string>

void ShaderUtils::UpdateLightingParametersInShader(const GuiParameters& guiParameters, Shader& shader)
{
    shader.setVec3("directionalLight.direction", guiParameters.directionalLight.direction);
    shader.setVec3("directionalLight.ambient", guiParameters.directionalLight.ambient);
    shader.setVec3("directionalLight.diffuse", guiParameters.directionalLight.diffuse);
    shader.setVec3("directionalLight.specular", guiParameters.directionalLight.specular);
    shader.setFloat("directionalLight.intensity", guiParameters.directionalLight.intensity);

    for (unsigned int i = 0; i < Config::numPointLights; ++i)
    {
        const std::string name = "pointLights[" + std::to_string(i) + "]";

        shader.setVec3(name + ".position", guiParameters.pointLights[i].position);
        shader.setVec3(name + ".ambient", guiParameters.pointLights[i].ambient);
        shader.setVec3(name + ".diffuse", guiParameters.pointLights[i].diffuse);
        shader.setVec3(name + ".specular", guiParameters.pointLights[i].specular);
        shader.setFloat(name + ".intensity", guiParameters.pointLights[i].intensity);
    }

    shader.setVec3("material.specular", 1.0f, 1.0f, 1.0f);
    shader.setFloat("material.shininess", 1.0f);
}
