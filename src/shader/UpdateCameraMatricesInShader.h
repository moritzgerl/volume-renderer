/**
* \file UpdateCameraMatricesInShader.h
*
* \brief Utility for updating camera transformation matrices in shaders.
*/

#ifndef UPDATE_CAMERA_MATRICES_IN_SHADER_H
#define UPDATE_CAMERA_MATRICES_IN_SHADER_H

class Camera;
class Shader;

namespace ShaderUtils
{
    /**
    * Updates camera-related uniforms in a shader program.
    *
    * Sets the view matrix, projection matrix, and camera position uniforms
    * in the shader based on the current camera state. The projection matrix
    * is calculated from the viewport dimensions.
    *
    * This function should be called before rendering any pass that requires
    * camera transformations (view-projection matrices, camera position for
    * lighting calculations, etc.).
    *
    * @param camera The camera containing view transformation state.
    * @param shader The shader to update with camera matrices.
    * @param viewportWidth Viewport width in pixels for projection matrix calculation.
    * @param viewportHeight Viewport height in pixels for projection matrix calculation.
    * @return void
    *
    * @see Camera for camera state and transformations.
    * @see Shader for shader uniform management.
    */
    void UpdateCameraMatricesInShader(const Camera& camera, const Shader& shader, float viewportWidth, float viewportHeight);
}

#endif
