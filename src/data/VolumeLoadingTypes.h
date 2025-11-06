#ifndef VOLUME_LOADING_TYPES_H
#define VOLUME_LOADING_TYPES_H

#include <data/VolumeData.h>
#include <data/VolumeLoadingError.h>

#include <expected>
#include <memory>

namespace Data
{
    using VolumeLoadingResult = std::expected<VolumeData, VolumeLoadingError>;
}

#endif
