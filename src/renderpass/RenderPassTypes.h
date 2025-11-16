/**
* \file RenderPassTypes.h
*
* \brief Type aliases for render pass collections.
*/

#ifndef RENDER_PASS_TYPES_H
#define RENDER_PASS_TYPES_H

#include <renderpass/RenderPass.h>

#include <vector>

/**
* \typedef RenderPasses
*
* \brief Collection of render passes forming the rendering pipeline.
*
* Type alias for a vector of RenderPass objects. The render passes are
* executed sequentially in the main loop to produce the final rendered image.
*
* @see RenderPass for individual render pass abstraction.
* @see MakeRenderPasses for creating the render pass sequence.
* @see Storage for storing the render pass collection.
*/
using RenderPasses = std::vector<RenderPass>;

#endif
