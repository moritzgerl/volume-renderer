#ifndef VOLUME_LOADING_TYPES_H
#define VOLUME_LOADING_TYPES_H

#include <volumedata/VolumeData.h>
#include <volumedata/VolumeLoadingError.h>

#include <expected>
#include <memory>

namespace VolumeData
{
    using VolumeLoadingResult = std::expected<VolumeData, VolumeLoadingError>;
}

#endif
