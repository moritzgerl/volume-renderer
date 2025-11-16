/**
* \file TextureId.h
*
* \brief Enumeration of textures used in the rendering pipeline.
*/

#ifndef TEXTURE_ID_H
#define TEXTURE_ID_H

/**
* \enum TextureId
*
* \brief Identifies textures for volume data, transfer functions, and SSAO.
*
* Each texture ID corresponds to a texture resource created via MakeTextures
* and stored in Storage. Textures include volume data, transfer functions,
* G-buffer attachments, SSAO outputs, and noise textures.
*
* @see Texture for texture creation and management.
* @see MakeTextures for texture initialization.
* @see Storage for texture storage and retrieval.
*/
enum class TextureId
{
    VolumeData,                    /**< 3D texture containing volume voxel data. */
    TransferFunction,              /**< 1D texture mapping scalar values to RGBA colors. */
    SsaoPosition,                  /**< G-buffer position texture for SSAO computation. */
    SsaoNormal,                    /**< G-buffer normal texture for SSAO computation. */
    SsaoAlbedo,                    /**< G-buffer albedo texture for final compositing. */
    Ssao,                          /**< Raw SSAO occlusion values (before blur). */
    SsaoBlur,                      /**< Blurred SSAO occlusion values (after blur). */
    SsaoNoise,                     /**< Random rotation noise texture for SSAO sampling. */
    SsaoPointLightsContribution,   /**< Point light contribution texture for lighting. */
    Unknown                        /**< Sentinel value for uninitialized or invalid texture IDs. */
};

#endif
