/**
* \file VolumeLoadingTypes.h
*
* \brief Type aliases for volume loading results.
*/

#ifndef VOLUME_LOADING_TYPES_H
#define VOLUME_LOADING_TYPES_H

#include <volumedata/VolumeData.h>
#include <volumedata/VolumeLoadingError.h>

#include <expected>
#include <memory>

namespace VolumeData
{
    /**
    * \typedef VolumeLoadingResult
    *
    * \brief Result type for volume loading operations.
    *
    * Type alias for std::expected that either contains VolumeData on success
    * or VolumeLoadingError on failure. This provides type-safe error handling
    * for volume file loading operations.
    *
    * The std::expected type eliminates the need for exceptions and makes
    * error handling explicit at the call site.
    *
    * @see VolumeData for the successfully loaded volume data.
    * @see VolumeLoadingError for error information.
    * @see LoadVolumeRaw for volume loading functions returning this type.
    */
    using VolumeLoadingResult = std::expected<VolumeData, VolumeLoadingError>;
}

#endif
