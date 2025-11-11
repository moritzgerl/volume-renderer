#include <volumedata/VolumeData.h>
#include <cstring>


VolumeData::VolumeData::VolumeData()
    : m_metadata()
    , m_data()
{
}

VolumeData::VolumeData::VolumeData(const VolumeMetadata& metadata)
    : m_metadata(metadata)
    , m_data()
{
    AllocateData();
}

void VolumeData::VolumeData::AllocateData()
{
    if (m_metadata.IsValid())
    {
        m_data.resize(m_metadata.GetTotalSizeInBytes());
    }
}

void VolumeData::VolumeData::AllocateData(size_t sizeInBytes)
{
    m_data.resize(sizeInBytes);
}

bool VolumeData::VolumeData::IsValid() const
{
    return m_metadata.IsValid() && m_data.size() == m_metadata.GetTotalSizeInBytes();
}

void VolumeData::VolumeData::Clear()
{
    m_data.clear();
    m_metadata = VolumeMetadata();
}

size_t VolumeData::VolumeData::GetVoxelIndex(uint32_t x, uint32_t y, uint32_t z) const
{
    // Row-major order: x varies fastest, then y, then z
    const size_t index = (static_cast<size_t>(z) * m_metadata.GetHeight() * m_metadata.GetWidth() +
                            static_cast<size_t>(y) * m_metadata.GetWidth() +
                            static_cast<size_t>(x)) * m_metadata.GetBytesPerVoxel();
    return index;
}

bool VolumeData::VolumeData::IsInBounds(uint32_t x, uint32_t y, uint32_t z) const
{
    return x < m_metadata.GetWidth() &&
            y < m_metadata.GetHeight() &&
            z < m_metadata.GetDepth();
}

uint8_t VolumeData::VolumeData::GetVoxel8(uint32_t x, uint32_t y, uint32_t z) const
{
    if (!IsInBounds(x, y, z) || m_metadata.GetBitsPerComponent() != 8 || m_metadata.GetComponents() != 1)
    {
        return 0;
    }

    const size_t index = GetVoxelIndex(x, y, z);
    return m_data[index];
}

bool VolumeData::VolumeData::SetVoxel8(uint32_t x, uint32_t y, uint32_t z, uint8_t value)
{
    if (!IsInBounds(x, y, z) || m_metadata.GetBitsPerComponent() != 8 || m_metadata.GetComponents() != 1)
    {
        return false;
    }

    const size_t index = GetVoxelIndex(x, y, z);
    m_data[index] = value;
    return true;
}

uint16_t VolumeData::VolumeData::GetVoxel16(uint32_t x, uint32_t y, uint32_t z) const
{
    if (!IsInBounds(x, y, z) || m_metadata.GetBitsPerComponent() != 16 || m_metadata.GetComponents() != 1)
    {
        return 0;
    }

    const size_t index = GetVoxelIndex(x, y, z);
    uint16_t value;
    std::memcpy(&value, &m_data[index], sizeof(uint16_t));
    return value;
}

bool VolumeData::VolumeData::SetVoxel16(uint32_t x, uint32_t y, uint32_t z, uint16_t value)
{
    if (!IsInBounds(x, y, z) || m_metadata.GetBitsPerComponent() != 16 || m_metadata.GetComponents() != 1)
    {
        return false;
    }

    const size_t index = GetVoxelIndex(x, y, z);
    std::memcpy(&m_data[index], &value, sizeof(uint16_t));
    return true;
}
