#include <storage/ShaderStorage.h>
#include <algorithm>
#include <stdexcept>

ShaderStorage::ShaderStorage(std::vector<Shader>&& shaders)
    : m_shaders(std::move(shaders))
{
}

Shader const& ShaderStorage::GetShader(ShaderId shaderId) const
{
    auto shaderIter = std::find_if(m_shaders.begin(), m_shaders.end(),
        [shaderId]
        (const Shader& shader)
        {
            return shader.GetShaderId() == shaderId;
        }
    );

    if (shaderIter == m_shaders.end())
    {
        throw std::out_of_range("ShaderStorage::GetShader - could not find shader with the specified ShaderId");
    }

    return *shaderIter;
}
