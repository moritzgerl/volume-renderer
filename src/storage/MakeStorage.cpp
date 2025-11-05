#include <storage/MakeStorage.h>
#include <storage/ElementStorage.h>
#include <buffers/MakeFrameBuffers.h>
#include <shader/MakeShaders.h>
#include <textures/MakeTextures.h>
#include <renderpass/MakeRenderPasses.h>

namespace Factory
{
    Storage MakeStorage(
        const Camera& camera,
        const DisplayProperties& displayProperties,
        const GuiParameters& guiParameters,
        const SsaoUtils& ssaoUtils,
        const ScreenQuad& screenQuad
    )
    {
        TextureStorage textureStorage(MakeTextures(ssaoUtils));
        ShaderStorage shaderStorage(MakeShaders(guiParameters, ssaoUtils, textureStorage));
        FrameBufferStorage frameBufferStorage(MakeFrameBuffers(textureStorage));
        RenderPassStorage renderPassStorage(MakeRenderPasses(camera, displayProperties, guiParameters, ssaoUtils, screenQuad, textureStorage, shaderStorage, frameBufferStorage));

        return Storage(
            std::move(textureStorage),
            std::move(shaderStorage),
            std::move(frameBufferStorage),
            std::move(renderPassStorage)
        );
    }
}
