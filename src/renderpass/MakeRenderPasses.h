#ifndef MAKE_RENDER_PASSES_H
#define MAKE_RENDER_PASSES_H

#include <renderpass/RenderPassTypes.h>

class Gui;
class InputHandler;
class Storage;

namespace Factory
{
    RenderPasses MakeRenderPasses(const Gui& gui, const InputHandler& inputHandler, const Storage& storage);
}

#endif
