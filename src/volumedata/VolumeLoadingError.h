/**
* \file VolumeLoadingError.h
*
* \brief Error codes for volume loading operations.
*/

#ifndef VOLUME_LOADING_ERROR_H
#define VOLUME_LOADING_ERROR_H

namespace VolumeData
{
    /**
    * \enum VolumeLoadingError
    *
    * \brief Error codes returned by volume loading functions.
    *
    * Enumerates all possible error conditions that can occur when loading
    * volume data from .raw files and their companion .dat metadata files.
    * Used with std::expected in VolumeLoadingResult to provide type-safe
    * error handling without exceptions.
    *
    * @see VolumeLoadingResult for the result type using this error enum.
    * @see LoadVolumeRaw for volume loading functions returning these errors.
    * @see VolumeMetadata for metadata validation.
    */
    enum class VolumeLoadingError
    {
        RawFileNotFound,         /**< The .raw file was not found at the specified path. */
        CannotOpenRawFile,       /**< Could not open the .raw file for reading. */
        FileSizeMismatch,        /**< The .raw file size does not match expected size from metadata. */
        ReadError,               /**< Error occurred while reading the .raw file. */
        MetadataFileNotFound,    /**< The companion .dat metadata file was not found. */
        CannotOpenMetadataFile,  /**< Could not open the .dat metadata file for reading. */
        MetadataParseError,      /**< Failed to parse metadata values from .dat file. */
        InvalidMetadata,         /**< Metadata validation failed (invalid dimensions, components, etc.). */
        InvalidVolumeData        /**< Volume data validation failed after loading. */
    };
}

#endif
