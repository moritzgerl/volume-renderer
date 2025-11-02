#include "MakeShaders.h"
#include <utils/FileSystem.h>

namespace Factory
{
    std::vector<Shader>&& MakeShaders()
    {
        std::vector<Shader> shaders;
        shaders.reserve(6);

        shaders.emplace_back(FileSystem::getPath("src/shaders/SsaoInput.vert").c_str(), FileSystem::getPath("src/shaders/SsaoInput.frag").c_str());
        shaders.emplace_back(FileSystem::getPath("src/shaders/Ssao.vert").c_str(), FileSystem::getPath("src/shaders/Ssao.frag").c_str());
        shaders.emplace_back(FileSystem::getPath("src/shaders/Ssao.vert").c_str(), FileSystem::getPath("src/shaders/SsaoBlur.frag").c_str());
        shaders.emplace_back(FileSystem::getPath("src/shaders/SsaoFinal.vert").c_str(), FileSystem::getPath("src/shaders/SsaoFinal.frag").c_str());
        shaders.emplace_back(FileSystem::getPath("src/shaders/DebugQuad.vert").c_str(), FileSystem::getPath("src/shaders/DebugQuadColor.frag").c_str());
        shaders.emplace_back(FileSystem::getPath("src/shaders/LightSource.vert").c_str(), FileSystem::getPath("src/shaders/LightSource.frag").c_str());

        return std::move(shaders);
    }
}
 