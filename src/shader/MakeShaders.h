#ifndef MAKE_SHADERS_H
#define MAKE_SHADERS_H

#include <shader/Shader.h>
#include <vector>

struct GuiParameters;
class SsaoUtils;
class TextureStorage;

namespace Factory
{
    std::vector<Shader> MakeShaders(
        const GuiParameters& guiParameters,
        const SsaoUtils& ssaoUtils,
        const TextureStorage& textureStorage
    );
}

#endif
