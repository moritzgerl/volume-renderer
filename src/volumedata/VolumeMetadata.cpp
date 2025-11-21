#include <volumedata/VolumeMetadata.h>

VolumeData::VolumeMetadata::VolumeMetadata()
    : m_width{0}
    , m_height{0}
    , m_depth{0}
    , m_components{1}
    , m_bitsPerComponent{8}
    , m_scaleX{1.0f}
    , m_scaleY{1.0f}
    , m_scaleZ{1.0f}
{
}

VolumeData::VolumeMetadata::VolumeMetadata(uint32_t width, uint32_t height, uint32_t depth,
                               uint32_t components, uint32_t bitsPerComponent)
    : m_width{width}
    , m_height{height}
    , m_depth{depth}
    , m_components{components}
    , m_bitsPerComponent{bitsPerComponent}
    , m_scaleX{1.0f}
    , m_scaleY{1.0f}
    , m_scaleZ{1.0f}
{
}

void VolumeData::VolumeMetadata::SetScale(float scaleX, float scaleY, float scaleZ)
{
    m_scaleX = scaleX;
    m_scaleY = scaleY;
    m_scaleZ = scaleZ;
}

size_t VolumeData::VolumeMetadata::GetVoxelCount() const
{
    return static_cast<size_t>(m_width) * m_height * m_depth;
}

size_t VolumeData::VolumeMetadata::GetBytesPerVoxel() const
{
    return m_components * (m_bitsPerComponent / 8);
}

size_t VolumeData::VolumeMetadata::GetTotalSizeInBytes() const
{
    return GetVoxelCount() * GetBytesPerVoxel();
}

bool VolumeData::VolumeMetadata::IsValid() const
{
    return m_width > 0 && m_height > 0 && m_depth > 0 &&
           m_components > 0 && m_bitsPerComponent > 0 &&
           (m_bitsPerComponent % 8 == 0);  // Must be byte-aligned
}
