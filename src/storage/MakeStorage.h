#ifndef MAKE_STORAGE_H
#define MAKE_STORAGE_H

#include <storage/Storage.h>
#include <glm/glm.hpp>

class Camera;
struct DisplayProperties;
struct GuiParameters;
class SsaoUtils;
class ScreenQuad;

namespace Factory
{
    Storage MakeStorage(
        const Camera& camera,
        const DisplayProperties& displayProperties,
        const GuiParameters& guiParameters,
        const SsaoUtils& ssaoUtils,
        const ScreenQuad& screenQuad
    );
}

#endif
