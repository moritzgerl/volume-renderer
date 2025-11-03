#ifndef STORAGE_H
#define STORAGE_H

#include "ShaderStorage.h"

class Storage
{
public:
    explicit Storage(ShaderStorage&& shaderStorage);

    // TODO use concepts
    Storage(const Storage&) = delete;
    Storage& operator=(const Storage&) = delete;
    Storage(Storage&&) = delete;
    Storage& operator=(Storage&&) = delete;

    ShaderStorage const& GetShaderStorage() const;
    Shader const& GetShader(ShaderId shaderId) const;

private:
    ShaderStorage m_shaderStorage;
};

#endif
