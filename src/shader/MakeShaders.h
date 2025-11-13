#ifndef MAKE_SHADERS_H
#define MAKE_SHADERS_H

#include <shader/Shader.h>
#include <storage/StorageTypes.h>
#include <vector>

struct GuiParameters;
class SsaoKernel;

namespace Factory
{
    std::vector<Shader> MakeShaders(
        const GuiParameters& guiParameters,
        const SsaoKernel& ssaoKernel,
        const TextureStorage& textureStorage
    );
}

#endif
