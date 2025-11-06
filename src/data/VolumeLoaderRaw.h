#ifndef VOLUME_LOADER_RAW_H
#define VOLUME_LOADER_RAW_H

#include <data/VolumeData.h>
#include <data/VolumeMetadata.h>
#include <filesystem>
#include <memory>

namespace Data {

/// Loader for headerless .raw volume files
///
/// The .raw format produced by pvm2raw has no header - it's pure binary voxel data.
/// Metadata must be provided externally either through:
/// 1. A companion .ini file with the same base name as the .raw file
/// 2. Direct specification via VolumeMetadata parameter
class VolumeLoaderRaw {
public:
    // TODO remove static
    // TODO Turn into free functions
    // TODO use std::expected
    /// Load a raw volume file using metadata from a companion .ini file
    ///
    /// @param rawFilePath Path to the .raw file
    /// @return VolumeData on success, nullptr on failure
    static std::unique_ptr<VolumeData> Load(const std::filesystem::path& rawFilePath);

    /// Load a raw volume file using provided metadata
    ///
    /// @param rawFilePath Path to the .raw file
    /// @param metadata Volume metadata (dimensions, components, bit depth, scaling)
    /// @return VolumeData on success, nullptr on failure
    static std::unique_ptr<VolumeData> Load(const std::filesystem::path& rawFilePath, const VolumeMetadata& metadata);

private:
    /// Load metadata from a companion .ini file
    /// Expected format:
    /// [Volume]
    /// Width=256
    /// Height=256
    /// Depth=512
    /// Components=1
    /// BitsPerComponent=8
    /// ScaleX=1.0
    /// ScaleY=1.0
    /// ScaleZ=1.0
    static bool LoadMetadataFromIni(const std::filesystem::path& iniFilePath, VolumeMetadata& metadata);

    /// Load raw binary data from file
    static bool LoadRawData(const std::filesystem::path& rawFilePath, VolumeData& volumeData);
};

} // namespace Data

#endif // VOLUME_LOADER_RAW_H
