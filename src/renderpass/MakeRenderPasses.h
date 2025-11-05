#ifndef MAKE_RENDER_PASSES_H
#define MAKE_RENDER_PASSES_H

#include <renderpass/RenderPass.h>
#include <storage/StorageTypes.h>

#include <vector>
#include <glm/glm.hpp>

class Camera;
struct DisplayProperties;
struct GuiParameters;
class SsaoUtils;
class ScreenQuad;

namespace Factory
{
    std::vector<RenderPass> MakeRenderPasses(
        const Camera& camera,
        const DisplayProperties& displayProperties,
        const GuiParameters& guiParameters,
        const SsaoUtils& ssaoUtils,
        const glm::mat4& lightSpaceMatrix,
        const ScreenQuad& screenQuad,
        const TextureStorage& textureStorage,
        const ShaderStorage& shaderStorage,
        const FrameBufferStorage& frameBufferStorage
    );
}

#endif
