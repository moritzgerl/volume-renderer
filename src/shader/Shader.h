/**
* \file Shader.h
*
* \brief Shader program compilation, linking, and uniform management.
*/

#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <shader/ShaderId.h>

#include <string>

/**
* \class Shader
*
* \brief Encapsulates an OpenGL shader program with uniform setting helpers.
*
* Handles compilation of vertex, fragment, and optional geometry shaders,
* linking them into a shader program, and providing convenient methods for
* setting uniform values of various types.
*
* Each Shader is identified by a ShaderId for type-safe retrieval from Storage.
* Shader paths are resolved via FileSystem::getPath() using the generated root_directory.h.
* Shaders are created via Factory::MakeShaders() which compiles all shader programs needed
* for the rendering pipeline.
*
* Provides uniform setters for common types: bool, int, float, vec2/3/4, and mat2/3/4.
*
* @see ShaderId for the enumeration of shader programs.
* @see Factory::MakeShaders for construction of all shaders.
* @see RenderPass for using shaders during rendering.
* @see UpdateCameraMatricesInShader for setting camera-related uniforms.
* @see UpdateLightingParametersInShader for setting lighting-related uniforms.
*/
class Shader
{
public:
    // TODO use strings
    /**
    * Constructor.
    * Compiles and links vertex, fragment, and optional geometry shaders into a program.
    * @param shaderId The ID identifying this shader program.
    * @param vertexPath The file path to the vertex shader source.
    * @param fragmentPath The file path to the fragment shader source.
    * @param geometryPath The file path to the geometry shader source (optional, nullptr if not used).
    */
    Shader(ShaderId shaderId, const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);

    ShaderId GetId() const;

    /**
    * Activates this shader program for rendering.
    * @return void
    */
    void Use() const;

    /**
    * Sets a boolean uniform in the shader.
    * @param name The uniform variable name.
    * @param value The boolean value to set.
    * @return void
    */
    void SetBool(const std::string& name, bool value) const;

    /**
    * Sets an integer uniform in the shader.
    * @param name The uniform variable name.
    * @param value The integer value to set.
    * @return void
    */
    void SetInt(const std::string& name, int value) const;

    /**
    * Sets a float uniform in the shader.
    * @param name The uniform variable name.
    * @param value The float value to set.
    * @return void
    */
    void SetFloat(const std::string& name, float value) const;
    void SetVec2(const std::string& name, const glm::vec2& value) const;
    void SetVec2(const std::string& name, float x, float y) const;
    void SetVec3(const std::string& name, const glm::vec3& value) const;
    void SetVec3(const std::string& name, float x, float y, float z) const;
    void SetVec4(const std::string& name, const glm::vec4& value) const;
    void SetVec4(const std::string& name, float x, float y, float z, float w) const;
    void SetMat2(const std::string& name, const glm::mat2& mat) const;
    void SetMat3(const std::string& name, const glm::mat3& mat) const;

    /**
    * Sets a 4x4 matrix uniform in the shader.
    * @param name The uniform variable name.
    * @param mat The matrix value to set.
    * @return void
    */
    void SetMat4(const std::string& name, const glm::mat4& mat) const;

private:
    /**
    * Checks for shader compilation or linking errors and throws an exception if found.
    * @param shader The shader or program ID to check.
    * @param type The type of shader ("VERTEX", "FRAGMENT", "GEOMETRY", or "PROGRAM").
    * @return void
    */
    void CheckCompileErrors(GLuint shader, std::string type);

private:
    ShaderId m_shaderId; /**< The ID of this shader program for identification. */
    unsigned int m_programId; /**< The OpenGL shader program handle. */
};

#endif
