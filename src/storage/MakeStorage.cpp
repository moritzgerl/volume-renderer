#include <storage/MakeStorage.h>
#include <storage/FrameBufferStorage.h>
#include <storage/ShaderStorage.h>
#include <storage/TextureStorage.h>
#include <storage/RenderPassStorage.h>
#include <buffers/MakeFrameBuffers.h>
#include <shader/MakeShaders.h>
#include <textures/MakeTextures.h>

namespace Factory
{
    Storage MakeStorage(const SsaoUtils& ssaoUtils)
    {
        TextureStorage textureStorage(MakeTextures(ssaoUtils));

        return Storage(
            std::forward<TextureStorage>(textureStorage),
            ShaderStorage(MakeShaders()),
            // TODO check if it is a problem to use the temporary textureStorage here
            FrameBufferStorage(MakeFrameBuffers(textureStorage)),
            RenderPassStorage(std::vector<RenderPass>()) // TODO: Create MakeRenderPasses factory
        );
    }
}
