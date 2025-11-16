/**
* \file RenderPassId.h
*
* \brief Enumeration of rendering pipeline stages.
*/

#ifndef RENDER_PASS_ID_H
#define RENDER_PASS_ID_H

/**
* \enum RenderPassId
*
* \brief Identifies rendering stages in the multi-pass pipeline.
*
* Each render pass represents a distinct stage in the rendering pipeline,
* executed sequentially to produce the final image. The passes implement
* volume ray-casting with Screen Space Ambient Occlusion (SSAO).
*
* @see RenderPass for the render pass abstraction.
* @see MakeRenderPasses for pipeline configuration.
* @see Storage for storing the collection of render passes.
*/
enum class RenderPassId
{
    Setup,        /**< Initial setup pass that clears the screen. */
    Volume,       /**< Volume ray-casting pass that renders the 3D volume data. */
    SsaoInput,    /**< Geometry pass that renders position, normal, and albedo to G-buffer. */
    Ssao,         /**< SSAO computation pass that samples occlusion from G-buffer. */
    SsaoBlur,     /**< Blur pass that smooths SSAO output to reduce noise. */
    SsaoFinal,    /**< Final compositing pass that combines volume rendering with SSAO. */
    LightSource,  /**< Light source visualization pass (optional). */
    Debug,        /**< Debug visualization pass for displaying intermediate buffers. */
    Unknown       /**< Sentinel value for uninitialized or invalid pass IDs. */
};

#endif
