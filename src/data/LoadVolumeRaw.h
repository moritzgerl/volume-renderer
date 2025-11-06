#ifndef LOAD_VOLUME_RAW_H
#define LOAD_VOLUME_RAW_H

#include <data/VolumeData.h>
#include <data/VolumeMetadata.h>
#include <filesystem>
#include <memory>

namespace Data
{
    /// Load a raw volume file using metadata from a companion .ini file
    ///
    /// The .raw format produced by pvm2raw has no header - it's pure binary voxel data.
    /// Metadata is read from a companion .ini file with the same base name as the .raw file.
    ///
    /// @param rawFilePath Path to the .raw file
    /// @return VolumeData on success, nullptr on failure
    std::unique_ptr<VolumeData> LoadVolumeRaw(const std::filesystem::path& rawFilePath);

    /// Load a raw volume file using provided metadata
    ///
    /// The .raw format produced by pvm2raw has no header - it's pure binary voxel data.
    /// Metadata must be provided externally via the metadata parameter.
    ///
    /// @param rawFilePath Path to the .raw file
    /// @param metadata Volume metadata (dimensions, components, bit depth, scaling)
    /// @return VolumeData on success, nullptr on failure
    std::unique_ptr<VolumeData> LoadVolumeRaw(const std::filesystem::path& rawFilePath, const VolumeMetadata& metadata);

}

#endif
