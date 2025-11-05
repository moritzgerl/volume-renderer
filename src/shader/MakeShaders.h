#ifndef MAKE_SHADERS_H
#define MAKE_SHADERS_H

#include <shader/Shader.h>
#include <vector>

struct GuiParameters;
class SsaoUtils;
template <typename ElementType, typename ElementIdType> class ElementStorage;
class Texture;
enum class TextureId;

namespace Factory
{
    std::vector<Shader> MakeShaders(
        const GuiParameters& guiParameters,
        const SsaoUtils& ssaoUtils,
        const ElementStorage<Texture, TextureId>& textureStorage
    );
}

#endif
