#ifndef MAKE_RENDER_PASSES_H
#define MAKE_RENDER_PASSES_H

#include <renderpass/RenderPassTypes.h>

class Storage;

namespace Factory
{
    RenderPasses MakeRenderPasses(const Storage& storage);
}

#endif
