#include <data/GetVolumeMetadataKey.h>
#include <algorithm>
#include <array>

namespace
{
    struct VolumeMetadataKeyMapping
    {
        std::string_view key;
        Data::VolumeMetadataKey value;
    };

    constexpr std::array<VolumeMetadataKeyMapping, 8> volumeMetadataKeyLookup =
    {{
        {"Width", Data::VolumeMetadataKey::Width},
        {"Height", Data::VolumeMetadataKey::Height},
        {"Depth", Data::VolumeMetadataKey::Depth},
        {"Components", Data::VolumeMetadataKey::Components},
        {"BitsPerComponent", Data::VolumeMetadataKey::BitsPerComponent},
        {"ScaleX", Data::VolumeMetadataKey::ScaleX},
        {"ScaleY", Data::VolumeMetadataKey::ScaleY},
        {"ScaleZ", Data::VolumeMetadataKey::ScaleZ}
    }};
}

Data::VolumeMetadataKey Data::GetVolumeMetadataKey(std::string_view key)
{
    auto it = std::find_if(volumeMetadataKeyLookup.begin(), volumeMetadataKeyLookup.end(),
        [key](const VolumeMetadataKeyMapping& mapping)
        {
            return mapping.key == key;
        });

    return (it != volumeMetadataKeyLookup.end()) ? it->value : VolumeMetadataKey::Unknown;
}
