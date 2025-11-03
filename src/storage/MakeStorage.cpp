#include <storage/MakeStorage.h>
#include <storage/ShaderStorage.h>
#include <shader/MakeShaders.h>

namespace Factory
{
    Storage MakeStorage()
    {
        return Storage(ShaderStorage(MakeShaders()));
    }
}
