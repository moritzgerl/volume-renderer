#ifndef VOLUME_DATA_H
#define VOLUME_DATA_H

#include <volumedata/VolumeMetadata.h>
#include <cstdint>
#include <vector>

namespace Data
{

    class VolumeData
    {
    public:
        VolumeData();
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
        void AllocateData();
        void AllocateData(size_t sizeInBytes);
        bool IsValid() const;
        void Clear();
        uint8_t GetVoxel8(uint32_t x, uint32_t y, uint32_t z) const;
        bool SetVoxel8(uint32_t x, uint32_t y, uint32_t z, uint8_t value);
        uint16_t GetVoxel16(uint32_t x, uint32_t y, uint32_t z) const;
        bool SetVoxel16(uint32_t x, uint32_t y, uint32_t z, uint16_t value);

    private:
        VolumeMetadata m_metadata;
        std::vector<uint8_t> m_data;

    
        size_t GetVoxelIndex(uint32_t x, uint32_t y, uint32_t z) const;
        bool IsInBounds(uint32_t x, uint32_t y, uint32_t z) const;
    };
}

#endif // VOLUME_DATA_H
