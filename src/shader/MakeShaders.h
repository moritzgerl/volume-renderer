#ifndef MAKE_SHADERS_H
#define MAKE_SHADERS_H

#include <shader/Shader.h>
#include <storage/StorageTypes.h>
#include <vector>

struct GuiParameters;
class SsaoUtils;

namespace Factory
{
    std::vector<Shader> MakeShaders(
        const GuiParameters& guiParameters,
        const SsaoUtils& ssaoUtils,
        const TextureStorage& textureStorage
    );
}

#endif
