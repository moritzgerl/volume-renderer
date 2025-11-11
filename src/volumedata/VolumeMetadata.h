#ifndef VOLUME_METADATA_H
#define VOLUME_METADATA_H

#include <cstdint>

namespace VolumeData
{

    class VolumeMetadata {
    public:
        VolumeMetadata();
        VolumeMetadata(uint32_t width, uint32_t height, uint32_t depth,
                       uint32_t components, uint32_t bitsPerComponent);

        // TODO check which functions we actually need
        uint32_t GetWidth() const { return m_width; }
        uint32_t GetHeight() const { return m_height; }
        uint32_t GetDepth() const { return m_depth; }
        uint32_t GetComponents() const { return m_components; }
        uint32_t GetBitsPerComponent() const { return m_bitsPerComponent; }
        float GetScaleX() const { return m_scaleX; }
        float GetScaleY() const { return m_scaleY; }
        float GetScaleZ() const { return m_scaleZ; }
        size_t GetVoxelCount() const;
        size_t GetBytesPerVoxel() const;
        size_t GetTotalSizeInBytes() const;

        void SetWidth(uint32_t width) { m_width = width; }
        void SetHeight(uint32_t height) { m_height = height; }
        void SetDepth(uint32_t depth) { m_depth = depth; }
        void SetComponents(uint32_t components) { m_components = components; }
        void SetBitsPerComponent(uint32_t bits) { m_bitsPerComponent = bits; }
        void SetScaleX(float scale) { m_scaleX = scale; }
        void SetScaleY(float scale) { m_scaleY = scale; }
        void SetScaleZ(float scale) { m_scaleZ = scale; }
        void SetScale(float scaleX, float scaleY, float scaleZ);

        bool IsValid() const;

    private:
        uint32_t m_width;
        uint32_t m_height;
        uint32_t m_depth;
        uint32_t m_components;        // Number of components per voxel (e.g., 1 for grayscale, 2 for grayscale+alpha)
        uint32_t m_bitsPerComponent;  // Bits per component (typically 8 or 16)
        float m_scaleX;               // Physical spacing in X direction
        float m_scaleY;               // Physical spacing in Y direction
        float m_scaleZ;               // Physical spacing in Z direction
    };

} // namespace VolumeData

#endif
