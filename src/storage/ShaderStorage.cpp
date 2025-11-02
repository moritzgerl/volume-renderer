#include <storage/ShaderStorage.h>
#include <algorithm>
#include <stdexcept>

ShaderStorage::ShaderStorage(std::vector<Shader>&& shaders)
    : m_shaders(std::move(shaders))
{
}

Shader const& ShaderStorage::GetShader(unsigned int id) const
{
    auto shaderIter = std::find_if(m_shaders.begin(), m_shaders.end(),
        [id]
        (const Shader& shader)
        {
            return shader.ID == id;
        }
    );

    if (shaderIter == m_shaders.end())
    {
        throw std::out_of_range("ShaderStorage::GetShader - could not find shader with ID " + std::to_string(id));
    }

    return *shaderIter;
}
