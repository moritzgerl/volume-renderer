/**
* \file VolumeData.h
*
* \brief 3D volume data storage and voxel access.
*/

#ifndef VOLUME_DATA_H
#define VOLUME_DATA_H

#include <volumedata/VolumeMetadata.h>
#include <cstdint>
#include <vector>

/**
* \namespace VolumeData
*
* \brief Volume data handling namespace.
*/
namespace VolumeData
{
    /**
    * \class VolumeData
    *
    * \brief Stores 3D volume data with metadata and provides voxel access.
    *
    * Encapsulates volumetric data as a contiguous array of bytes with associated metadata
    * (dimensions, bit depth). Supports both 8-bit and 16-bit voxel data with indexed access.
    *
    * Volume data is loaded from raw files via LoadVolumeRaw() and converted to a 3D OpenGL
    * texture via MakeVolumeDataTexture(). The volume is rendered using ray-casting in the
    * fragment shader.
    *
    * @see VolumeMetadata for volume dimensions and bit depth information.
    * @see LoadVolumeRaw for loading volume data from raw files.
    * @see Factory::MakeVolumeDataTexture for creating 3D textures from volume data.
    */
    class VolumeData
    {
    public:
        /**
        * Default constructor.
        */
        VolumeData();

        /**
        * Constructor.
        * @param metadata The volume metadata (dimensions, bit depth).
        */
        explicit VolumeData(const VolumeMetadata& metadata);

        VolumeData(const VolumeData&) = default;
        VolumeData& operator=(const VolumeData&) = default;
        VolumeData(VolumeData&&) noexcept = default;
        VolumeData& operator=(VolumeData&&) noexcept = default;

        const VolumeMetadata& GetMetadata() const { return m_metadata; }
        VolumeMetadata& GetMetadata() { return m_metadata; }
        void SetMetadata(const VolumeMetadata& metadata) { m_metadata = metadata; }

        // TODO check which functions we actually need
        const std::vector<uint8_t>& GetData() const { return m_data; }
        std::vector<uint8_t>& GetData() { return m_data; }
        const uint8_t* GetDataPtr() const { return m_data.data(); }
        uint8_t* GetDataPtr() { return m_data.data(); }
        size_t GetSizeInBytes() const { return m_data.size(); }

        /**
        * Allocates data storage based on metadata dimensions.
        * @return void
        */
        void AllocateData();

        /**
        * Allocates data storage with specified size.
        * @param sizeInBytes The size in bytes to allocate.
        * @return void
        */
        void AllocateData(size_t sizeInBytes);

        /**
        * Checks if volume data is valid (has metadata and allocated data).
        * @return bool True if valid, false otherwise.
        */
        bool IsValid() const;

        /**
        * Clears all volume data and resets metadata.
        * @return void
        */
        void Clear();

        /**
        * Gets an 8-bit voxel value at the specified coordinates.
        * @param x The x coordinate.
        * @param y The y coordinate.
        * @param z The z coordinate.
        * @return uint8_t The voxel value.
        */
        uint8_t GetVoxel8(uint32_t x, uint32_t y, uint32_t z) const;

        /**
        * Sets an 8-bit voxel value at the specified coordinates.
        * @param x The x coordinate.
        * @param y The y coordinate.
        * @param z The z coordinate.
        * @param value The voxel value to set.
        * @return bool True if successful, false if out of bounds.
        */
        bool SetVoxel8(uint32_t x, uint32_t y, uint32_t z, uint8_t value);

        /**
        * Gets a 16-bit voxel value at the specified coordinates.
        * @param x The x coordinate.
        * @param y The y coordinate.
        * @param z The z coordinate.
        * @return uint16_t The voxel value.
        */
        uint16_t GetVoxel16(uint32_t x, uint32_t y, uint32_t z) const;

        /**
        * Sets a 16-bit voxel value at the specified coordinates.
        * @param x The x coordinate.
        * @param y The y coordinate.
        * @param z The z coordinate.
        * @param value The voxel value to set.
        * @return bool True if successful, false if out of bounds.
        */
        bool SetVoxel16(uint32_t x, uint32_t y, uint32_t z, uint16_t value);

    private:
        VolumeMetadata m_metadata; /**< Volume metadata (dimensions, bit depth). */
        std::vector<uint8_t> m_data; /**< Contiguous array of voxel data. */

        /**
        * Computes the linear index for 3D voxel coordinates.
        */
        size_t GetVoxelIndex(uint32_t x, uint32_t y, uint32_t z) const;

        /**
        * Checks if coordinates are within volume bounds.
        */
        bool IsInBounds(uint32_t x, uint32_t y, uint32_t z) const;
    };
}

#endif // VOLUME_DATA_H
