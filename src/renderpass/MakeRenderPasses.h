/**
* \file MakeRenderPasses.h
*
* \brief Factory function for creating and configuring all render passes.
*/

#ifndef MAKE_RENDER_PASSES_H
#define MAKE_RENDER_PASSES_H

#include <renderpass/RenderPassTypes.h>

class Gui;
class InputHandler;
class Storage;

namespace Factory
{
    /**
    * Creates and configures all render passes for the rendering pipeline.
    *
    * Constructs the complete sequence of render passes including Setup, Volume,
    * SSAO Input, SSAO, SSAO Blur, SSAO Final, Light Source, and Debug passes.
    * Each render pass is configured with appropriate shaders, framebuffers,
    * textures, and rendering functions. The render passes encapsulate all
    * rendering logic for each stage of the pipeline.
    *
    * @param gui GUI component for rendering the user interface.
    * @param inputHandler Input handler for display property queries.
    * @param storage Storage containing all rendering resources (shaders, textures, framebuffers, etc.).
    * @return Vector of configured RenderPass objects indexed by RenderPassId.
    *
    * @see RenderPass for render pass abstraction.
    * @see RenderPassId for render pass identifier enumeration.
    * @see Storage for centralized resource management.
    */
    RenderPasses MakeRenderPasses(const Gui& gui, const InputHandler& inputHandler, const Storage& storage);
}

#endif
