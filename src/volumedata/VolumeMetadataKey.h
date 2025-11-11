#ifndef VOLUME_METADATA_KEY_H
#define VOLUME_METADATA_KEY_H

namespace VolumeData
{
    /// Metadata keys for volume file parsing
    enum class VolumeMetadataKey
    {
        Width,
        Height,
        Depth,
        Components,
        BitsPerComponent,
        ScaleX,
        ScaleY,
        ScaleZ,
        Unknown
    };
}

#endif
