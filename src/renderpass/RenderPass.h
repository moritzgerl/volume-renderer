/**
* \file RenderPass.h
*
* \brief Self-contained rendering stage abstraction.
*/

#ifndef RENDER_PASS_H
#define RENDER_PASS_H

#include <renderpass/RenderPassId.h>
#include <functional>
#include <vector>

class Shader;
class FrameBuffer;
class Texture;

/**
* \class RenderPass
*
* \brief Encapsulates a single rendering stage in the pipeline.
*
* Each RenderPass is a self-contained object representing one stage of the rendering pipeline.
* It contains references to the shader, framebuffer, and textures needed for that stage,
* along with prepare and render functions that configure OpenGL state and execute drawing commands.
*
* RenderPasses are created via Factory::MakeRenderPasses() which configures the entire pipeline,
* and they are executed sequentially in the main loop by calling Render() on each pass.
*
* The prepare function typically sets up OpenGL state (depth testing, blending, viewport),
* while the render function executes the actual drawing commands (binding resources, drawing primitives).
*
* @see RenderPassId for the enumeration of all rendering stages.
* @see Factory::MakeRenderPasses for construction of the rendering pipeline.
* @see Main.cpp for the sequential execution of render passes in the main loop.
*/
class RenderPass
{
public:
    /**
    * Constructor.
    * @param renderPassId The ID identifying this render pass.
    * @param shader The shader program to use for this pass.
    * @param frameBuffer The framebuffer to render into.
    * @param textures The textures to bind for this pass (moved into the render pass).
    * @param prepareFunction The function to configure OpenGL state before rendering (moved into the render pass).
    * @param renderFunction The function to execute drawing commands (moved into the render pass).
    */
    RenderPass(
        RenderPassId renderPassId,
        const Shader& shader,
        const FrameBuffer& frameBuffer,
        std::vector<std::reference_wrapper<const Texture>>&& textures,
        std::function<void()>&& prepareFunction,
        std::function<void()>&& renderFunction
    );

    RenderPassId GetId() const;

    /**
    * Executes this render pass.
    * Calls the prepare function to set up OpenGL state, then calls the render function to draw.
    * @return void
    */
    void Render() const;

private:
    RenderPassId m_renderPassId; /**< The ID of this render pass for identification. */
    const Shader& m_shader; /**< The shader program for this pass. */
    const FrameBuffer& m_frameBuffer; /**< The framebuffer to render into. */
    std::vector<std::reference_wrapper<const Texture>> m_textures; /**< The textures to bind for this pass. */
    std::function<void()> m_prepareFunction; /**< Function to configure OpenGL state before rendering. */
    std::function<void()> m_renderFunction; /**< Function to execute drawing commands. */
};

#endif
