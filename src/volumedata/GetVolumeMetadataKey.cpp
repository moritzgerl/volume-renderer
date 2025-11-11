#include <volumedata/GetVolumeMetadataKey.h>
#include <algorithm>
#include <array>

namespace
{
    struct VolumeMetadataKeyMapping
    {
        std::string_view key;
        VolumeData::VolumeMetadataKey value;
    };

    constexpr std::array<VolumeMetadataKeyMapping, 8> volumeMetadataKeyLookup =
    {{
        {"Width", VolumeData::VolumeMetadataKey::Width},
        {"Height", VolumeData::VolumeMetadataKey::Height},
        {"Depth", VolumeData::VolumeMetadataKey::Depth},
        {"Components", VolumeData::VolumeMetadataKey::Components},
        {"BitsPerComponent", VolumeData::VolumeMetadataKey::BitsPerComponent},
        {"ScaleX", VolumeData::VolumeMetadataKey::ScaleX},
        {"ScaleY", VolumeData::VolumeMetadataKey::ScaleY},
        {"ScaleZ", VolumeData::VolumeMetadataKey::ScaleZ}
    }};
}

VolumeData::VolumeMetadataKey VolumeData::GetVolumeMetadataKey(std::string_view key)
{
    auto it = std::find_if(volumeMetadataKeyLookup.begin(), volumeMetadataKeyLookup.end(),
        [key](const VolumeMetadataKeyMapping& mapping)
        {
            return mapping.key == key;
        });

    return (it != volumeMetadataKeyLookup.end()) ? it->value : VolumeMetadataKey::Unknown;
}
