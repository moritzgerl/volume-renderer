#include <volumedata/GetVolumeMetadataKey.h>
#include <algorithm>
#include <array>

namespace
{
    using Key = VolumeData::VolumeMetadataKey;

    struct VolumeMetadataKeyMapping
    {
        std::string_view stringKey;
        Key enumKey;
    };

    constexpr std::array<VolumeMetadataKeyMapping, 8> volumeMetadataKeyLookup =
    {{
        {"Width", Key::Width},
        {"Height", Key::Height},
        {"Depth", Key::Depth},
        {"Components", Key::Components},
        {"BitsPerComponent", Key::BitsPerComponent},
        {"ScaleX", Key::ScaleX},
        {"ScaleY", Key::ScaleY},
        {"ScaleZ", Key::ScaleZ}
    }};
}

VolumeData::VolumeMetadataKey VolumeData::GetVolumeMetadataKey(std::string_view stringKey)
{
    auto it = std::find_if(volumeMetadataKeyLookup.begin(), volumeMetadataKeyLookup.end(),
        [stringKey](const VolumeMetadataKeyMapping& mapping)
        {
            return mapping.stringKey == stringKey;
        });

    return (it != volumeMetadataKeyLookup.end()) ? it->enumKey : VolumeMetadataKey::Unknown;
}
