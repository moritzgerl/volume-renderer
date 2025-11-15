/**
* \file VolumeMetadata.h
*
* \brief Metadata for 3D volume datasets.
*/

#ifndef VOLUME_METADATA_H
#define VOLUME_METADATA_H

#include <cstdint>

namespace VolumeData
{

    /**
    * \class VolumeMetadata
    *
    * \brief Stores dimensional and format information for volume datasets.
    *
    * Contains all metadata necessary to interpret raw volume data files, including
    * dimensions (width, height, depth), data format (components, bits per component),
    * and physical spacing (scale factors for anisotropic datasets).
    *
    * Metadata is typically loaded from a .dat file accompanying the raw volume data.
    * The metadata is used to create 3D textures and properly scale the volume during
    * rendering.
    *
    * @see LoadVolumeRaw for loading metadata from .dat files.
    * @see VolumeData for the actual volume voxel data.
    * @see MakeVolumeDataTexture for creating 3D textures from volume data.
    */
    class VolumeMetadata {
    public:
        /**
        * Default constructor.
        * Initializes metadata with zero dimensions and default values.
        */
        VolumeMetadata();

        /**
        * Constructor with parameters.
        * @param width Volume width in voxels.
        * @param height Volume height in voxels.
        * @param depth Volume depth in voxels.
        * @param components Number of components per voxel (e.g., 1 for grayscale).
        * @param bitsPerComponent Bits per component (typically 8 or 16).
        */
        VolumeMetadata(uint32_t width, uint32_t height, uint32_t depth,
                       uint32_t components, uint32_t bitsPerComponent);

        /**
        * Gets the volume width in voxels.
        * @return Width dimension.
        */
        uint32_t GetWidth() const { return m_width; }

        /**
        * Gets the volume height in voxels.
        * @return Height dimension.
        */
        uint32_t GetHeight() const { return m_height; }

        /**
        * Gets the volume depth in voxels.
        * @return Depth dimension.
        */
        uint32_t GetDepth() const { return m_depth; }

        /**
        * Gets the number of components per voxel.
        * @return Component count (e.g., 1 for grayscale, 2 for grayscale+alpha).
        */
        uint32_t GetComponents() const { return m_components; }

        /**
        * Gets the bits per component.
        * @return Bits per component (typically 8 or 16).
        */
        uint32_t GetBitsPerComponent() const { return m_bitsPerComponent; }

        /**
        * Gets the physical spacing scale factor in the X direction.
        * @return Scale factor for X dimension.
        */
        float GetScaleX() const { return m_scaleX; }

        /**
        * Gets the physical spacing scale factor in the Y direction.
        * @return Scale factor for Y dimension.
        */
        float GetScaleY() const { return m_scaleY; }

        /**
        * Gets the physical spacing scale factor in the Z direction.
        * @return Scale factor for Z dimension.
        */
        float GetScaleZ() const { return m_scaleZ; }

        /**
        * Calculates the total number of voxels.
        * @return width * height * depth.
        */
        size_t GetVoxelCount() const;

        /**
        * Calculates the bytes per voxel.
        * @return (components * bitsPerComponent) / 8.
        */
        size_t GetBytesPerVoxel() const;

        /**
        * Calculates the total size in bytes.
        * @return GetVoxelCount() * GetBytesPerVoxel().
        */
        size_t GetTotalSizeInBytes() const;

        /**
        * Sets the volume width.
        * @param width Width dimension in voxels.
        */
        void SetWidth(uint32_t width) { m_width = width; }

        /**
        * Sets the volume height.
        * @param height Height dimension in voxels.
        */
        void SetHeight(uint32_t height) { m_height = height; }

        /**
        * Sets the volume depth.
        * @param depth Depth dimension in voxels.
        */
        void SetDepth(uint32_t depth) { m_depth = depth; }

        /**
        * Sets the number of components per voxel.
        * @param components Component count.
        */
        void SetComponents(uint32_t components) { m_components = components; }

        /**
        * Sets the bits per component.
        * @param bits Bits per component.
        */
        void SetBitsPerComponent(uint32_t bits) { m_bitsPerComponent = bits; }

        /**
        * Sets the physical spacing scale factor in the X direction.
        * @param scale Scale factor for X dimension.
        */
        void SetScaleX(float scale) { m_scaleX = scale; }

        /**
        * Sets the physical spacing scale factor in the Y direction.
        * @param scale Scale factor for Y dimension.
        */
        void SetScaleY(float scale) { m_scaleY = scale; }

        /**
        * Sets the physical spacing scale factor in the Z direction.
        * @param scale Scale factor for Z dimension.
        */
        void SetScaleZ(float scale) { m_scaleZ = scale; }

        /**
        * Sets all three physical spacing scale factors at once.
        * @param scaleX Scale factor for X dimension.
        * @param scaleY Scale factor for Y dimension.
        * @param scaleZ Scale factor for Z dimension.
        * @return void
        */
        void SetScale(float scaleX, float scaleY, float scaleZ);

        /**
        * Validates that metadata contains sensible values.
        * @return True if metadata is valid (non-zero dimensions and components), false otherwise.
        */
        bool IsValid() const;

    private:
        uint32_t m_width; /**< Volume width in voxels. */
        uint32_t m_height; /**< Volume height in voxels. */
        uint32_t m_depth; /**< Volume depth in voxels. */
        uint32_t m_components; /**< Number of components per voxel (e.g., 1 for grayscale, 2 for grayscale+alpha). */
        uint32_t m_bitsPerComponent; /**< Bits per component (typically 8 or 16). */
        float m_scaleX; /**< Physical spacing in X direction. */
        float m_scaleY; /**< Physical spacing in Y direction. */
        float m_scaleZ; /**< Physical spacing in Z direction. */
    };

} // namespace VolumeData

#endif
