#ifndef MAKE_RENDER_PASSES_H
#define MAKE_RENDER_PASSES_H

#include <renderpass/RenderPass.h>

#include <vector>
#include <glm/glm.hpp>

class Storage;
class ScreenQuad;
class Camera;
struct DisplayProperties;
struct GuiParameters;
class SsaoUtils;

namespace Factory
{
    std::vector<RenderPass> MakeRenderPasses(
        const Storage& storage,
        const ScreenQuad& screenQuad,
        const Camera& camera,
        const DisplayProperties& displayProperties,
        const GuiParameters& guiParameters,
        const SsaoUtils& ssaoUtils,
        const glm::mat4& lightSpaceMatrix
    );
}

#endif
