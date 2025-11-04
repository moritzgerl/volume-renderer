#include <storage/ShaderStorage.h>

ShaderStorage::ShaderStorage(std::vector<Shader>&& shaders)
    : m_storage(std::move(shaders))
{
}

Shader const& ShaderStorage::GetShader(ShaderId shaderId) const
{
    return m_storage.GetElement(shaderId);
}
