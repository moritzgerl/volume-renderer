#ifndef GET_VOLUME_METADATA_KEY_H
#define GET_VOLUME_METADATA_KEY_H

#include <volumedata/VolumeMetadataKey.h>
#include <string_view>

namespace VolumeData
{   
    VolumeMetadataKey GetVolumeMetadataKey(std::string_view key);
}

#endif
