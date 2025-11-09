#ifndef UPDATE_CAMERA_MATRICES_IN_SHADER_H
#define UPDATE_CAMERA_MATRICES_IN_SHADER_H

class Camera;
class Shader;

namespace ShaderUtils
{
    void UpdateCameraMatricesInShader(const Camera& camera, const Shader& shader, float viewportWidth, float viewportHeight);
}

#endif
