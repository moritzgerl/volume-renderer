#ifndef VOLUME_LOAD_ERROR_H
#define VOLUME_LOAD_ERROR_H

namespace Data
{
    /// Error codes for volume loading operations
    enum class VolumeLoadError
    {
        /// The .raw file was not found at the specified path
        RawFileNotFound,

        /// Could not open the .raw file for reading
        CannotOpenRawFile,

        /// The .raw file size does not match expected size from metadata
        FileSizeMismatch,

        /// Error occurred while reading the .raw file
        ReadError,

        /// The companion .ini metadata file was not found
        MetadataFileNotFound,

        /// Could not open the .ini metadata file for reading
        CannotOpenMetadataFile,

        /// Failed to parse metadata values from .ini file
        MetadataParseError,

        /// Metadata validation failed (invalid dimensions, components, etc.)
        InvalidMetadata,

        /// Volume data validation failed after loading
        InvalidVolumeData
    };
}

#endif
