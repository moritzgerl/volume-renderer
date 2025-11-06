#ifndef GET_VOLUME_METADATA_KEY_H
#define GET_VOLUME_METADATA_KEY_H

#include <data/VolumeMetadataKey.h>
#include <string_view>

namespace Data
{   
    VolumeMetadataKey GetVolumeMetadataKey(std::string_view key);
}

#endif
