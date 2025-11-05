#ifndef MAKE_RENDER_PASSES_H
#define MAKE_RENDER_PASSES_H

#include <renderpass/RenderPass.h>

#include <vector>
#include <glm/glm.hpp>

class Camera;
struct DisplayProperties;
struct GuiParameters;
class SsaoUtils;
class ScreenQuad;
template <typename ElementType, typename ElementIdType> class ElementStorage;
class Texture;
enum class TextureId;
class Shader;
enum class ShaderId;
class FrameBuffer;
enum class FrameBufferId;

namespace Factory
{
    std::vector<RenderPass> MakeRenderPasses(
        const Camera& camera,
        const DisplayProperties& displayProperties,
        const GuiParameters& guiParameters,
        const SsaoUtils& ssaoUtils,
        const glm::mat4& lightSpaceMatrix,
        const ScreenQuad& screenQuad,
        const ElementStorage<Texture, TextureId>& textureStorage,
        const ElementStorage<Shader, ShaderId>& shaderStorage,
        const ElementStorage<FrameBuffer, FrameBufferId>& frameBufferStorage
    );
}

#endif
