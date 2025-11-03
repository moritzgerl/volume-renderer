#include "Storage.h"

Storage::Storage(ShaderStorage&& shaderStorage)
    : m_shaderStorage(std::move(shaderStorage))
{
}

ShaderStorage const& Storage::GetShaderStorage() const
{
    return m_shaderStorage;
}

Shader const& Storage::GetShader(ShaderId shaderId) const
{
    return m_shaderStorage.GetShader(shaderId);
}
