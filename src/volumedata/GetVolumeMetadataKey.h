/**
* \file GetVolumeMetadataKey.h
*
* \brief Function for converting string keys to VolumeMetadataKey enum values.
*/

#ifndef GET_VOLUME_METADATA_KEY_H
#define GET_VOLUME_METADATA_KEY_H

#include <volumedata/VolumeMetadataKey.h>
#include <string_view>

namespace VolumeData
{
    /**
    * Converts a string key to a VolumeMetadataKey enum value.
    *
    * Maps metadata key strings from .dat files (e.g., "Width", "Height",
    * "BitsPerComponent") to their corresponding enum values for type-safe
    * metadata field identification. Returns VolumeMetadataKey::Unknown if
    * the key string is not recognized.
    *
    * @param key The metadata key string from the .dat file.
    * @return The corresponding VolumeMetadataKey enum value.
    *
    * @see VolumeMetadataKey for metadata key enumeration.
    * @see LoadVolumeRaw for loading metadata from .dat files.
    */
    VolumeMetadataKey GetVolumeMetadataKey(std::string_view key);
}

#endif
