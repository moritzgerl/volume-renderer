#ifndef UPDATE_MATRICES_IN_SHADER_H
#define UPDATE_MATRICES_IN_SHADER_H

class Camera;
class Shader;

namespace ShaderUtils
{
    void UpdateMatricesInShader(const Camera& camera, Shader& shader);
}

#endif
