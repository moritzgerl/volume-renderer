#include <storage/MakeStorage.h>
#include <storage/ShaderStorage.h>
#include <storage/TextureStorage.h>
#include <shader/MakeShaders.h>
#include <textures/MakeTextures.h>

namespace Factory
{
    Storage MakeStorage(const SsaoUtils& ssaoUtils)
    {
        return Storage(
            ShaderStorage(MakeShaders()),
            TextureStorage(MakeTextures(ssaoUtils))
        );
    }
}
