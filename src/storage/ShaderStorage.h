#ifndef SHADER_STORAGE_H
#define SHADER_STORAGE_H

#include <shader/Shader.h>
#include <shader/ShaderId.h>
#include <storage/ElementStorage.h>

class ShaderStorage
{
public:
    explicit ShaderStorage(std::vector<Shader>&& shaders);
    Shader const& GetShader(ShaderId shaderId) const;

private:
    ElementStorage<Shader, ShaderId> m_storage;
};

#endif
