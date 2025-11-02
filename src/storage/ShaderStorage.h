#ifndef SHADER_STORAGE_H
#define SHADER_STORAGE_H

#include <shader/Shader.h>
#include <vector>

class ShaderStorage
{
public:
    ShaderStorage(std::vector<Shader>&& shaders);
    Shader const& GetShader(unsigned int id) const;

private:
    std::vector<Shader> m_shaders;
};

#endif
