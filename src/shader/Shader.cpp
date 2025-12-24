// Copyright https://learnopengl.com/

#include <shader/Shader.h>

#include <glad/glad.h>

#include <iostream>
#include <string>

Shader::Shader(ShaderId shaderId, std::string_view vertexSource, std::string_view fragmentSource, std::string_view geometrySource)
    : m_shaderId{shaderId}
    , m_programId{0}
{
    const auto* const vShaderCode = vertexSource.data();
    const auto* const fShaderCode = fragmentSource.data();
    const auto vShaderLength = static_cast<GLint>(vertexSource.size());
    const auto fShaderLength = static_cast<GLint>(fragmentSource.size());

    // Compile vertex shader
    auto vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, &vShaderLength);
    glCompileShader(vertex);
    CheckCompileErrors(vertex, "VERTEX");

    // Compile fragment shader
    auto fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, &fShaderLength);
    glCompileShader(fragment);
    CheckCompileErrors(fragment, "FRAGMENT");

    // Compile geometry shader if provided
    auto geometry = unsigned int{0};
    if (!geometrySource.empty())
    {
        const auto* const gShaderCode = geometrySource.data();
        const auto gShaderLength = static_cast<GLint>(geometrySource.size());
        geometry = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometry, 1, &gShaderCode, &gShaderLength);
        glCompileShader(geometry);
        CheckCompileErrors(geometry, "GEOMETRY");
    }

    // Link shader program
    m_programId = glCreateProgram();
    glAttachShader(m_programId, vertex);
    glAttachShader(m_programId, fragment);
    if (!geometrySource.empty())
    {
        glAttachShader(m_programId, geometry);
    }
    glLinkProgram(m_programId);
    CheckCompileErrors(m_programId, "PROGRAM");

    // Delete shaders as they're linked into the program now
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    if (!geometrySource.empty())
    {
        glDeleteShader(geometry);
    }
}

Shader::~Shader()
{
    if (m_programId != 0)
    {
        glDeleteProgram(m_programId);
    }
}

Shader::Shader(Shader&& other) noexcept
    : m_shaderId{other.m_shaderId}
    , m_programId{other.m_programId}
{
    other.m_programId = 0;
}

Shader& Shader::operator=(Shader&& other) noexcept
{
    if (this != &other)
    {
        if (m_programId != 0)
        {
            glDeleteProgram(m_programId);
        }
        m_shaderId = other.m_shaderId;
        m_programId = other.m_programId;
        other.m_programId = 0;
    }
    return *this;
}

ShaderId Shader::GetId() const
{
    return m_shaderId;
}

void Shader::Use() const
{
    glUseProgram(m_programId);
}

void Shader::SetBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(m_programId, name.c_str()), (int)value);
}

void Shader::SetInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(m_programId, name.c_str()), value);
}

void Shader::SetFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(m_programId, name.c_str()), value);
}

void Shader::SetVec2(const std::string& name, const glm::vec2& value) const
{
    glUniform2fv(glGetUniformLocation(m_programId, name.c_str()), 1, &value[0]);
}

void Shader::SetVec2(const std::string& name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(m_programId, name.c_str()), x, y);
}

void Shader::SetVec3(const std::string& name, const glm::vec3& value) const
{
    glUniform3fv(glGetUniformLocation(m_programId, name.c_str()), 1, &value[0]);
}

void Shader::SetVec3(const std::string& name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(m_programId, name.c_str()), x, y, z);
}

void Shader::SetVec4(const std::string& name, const glm::vec4& value) const
{
    glUniform4fv(glGetUniformLocation(m_programId, name.c_str()), 1, &value[0]);
}

void Shader::SetVec4(const std::string& name, float x, float y, float z, float w) const
{
    glUniform4f(glGetUniformLocation(m_programId, name.c_str()), x, y, z, w);
}

void Shader::SetMat2(const std::string& name, const glm::mat2& mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(m_programId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetMat3(const std::string& name, const glm::mat3& mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(m_programId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetMat4(const std::string& name, const glm::mat4& mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_programId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::CheckCompileErrors(GLuint shader, std::string type)
{
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}
