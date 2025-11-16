/**
* \file ShaderId.h
*
* \brief Enumeration of shader programs used in the rendering pipeline.
*/

#ifndef SHADER_ID_H
#define SHADER_ID_H

/**
* \enum ShaderId
*
* \brief Identifies shader programs for different rendering stages.
*
* Each shader ID corresponds to a compiled and linked shader program used
* by a specific render pass. Shaders are created via MakeShaders and stored
* in Storage for retrieval by render passes.
*
* @see Shader for shader compilation and management.
* @see MakeShaders for shader program creation.
* @see Storage for shader storage and retrieval.
*/
enum class ShaderId
{
    Volume,       /**< Volume ray-casting shader for rendering 3D volume data. */
    SsaoInput,    /**< G-buffer generation shader for SSAO (position, normal, albedo). */
    Ssao,         /**< Screen Space Ambient Occlusion computation shader. */
    SsaoBlur,     /**< Bilateral blur shader for smoothing SSAO output. */
    SsaoFinal,    /**< Final compositing shader that combines volume with SSAO. */
    DebugQuad,    /**< Debug visualization shader for displaying intermediate textures. */
    LightSource,  /**< Light source visualization shader. */
    Unknown       /**< Sentinel value for uninitialized or invalid shader IDs. */
};

#endif
