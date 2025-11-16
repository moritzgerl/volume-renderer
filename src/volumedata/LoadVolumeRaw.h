/**
* \file LoadVolumeRaw.h
*
* \brief Functions for loading raw volume data files.
*/

#ifndef LOAD_VOLUME_RAW_H
#define LOAD_VOLUME_RAW_H

#include <volumedata/VolumeLoadingTypes.h>
#include <volumedata/VolumeMetadata.h>

#include <filesystem>

namespace VolumeData
{
    /**
    * Loads a raw volume file using metadata from a companion .dat file.
    *
    * The .raw format produced by pvm2raw contains no header - it's pure binary
    * voxel data. Metadata (dimensions, bit depth, scaling) is read from a
    * companion .dat file with the same base name as the .raw file.
    *
    * For example, given "volume.raw", this function looks for "volume.dat"
    * containing the metadata.
    *
    * @param rawFilePath Path to the .raw file.
    * @return VolumeLoadingResult containing VolumeData on success, or VolumeLoadingError on failure.
    *
    * @see VolumeData for the loaded volume structure.
    * @see VolumeMetadata for metadata format.
    * @see VolumeLoadingResult for the result type.
    */
    VolumeLoadingResult LoadVolumeRaw(const std::filesystem::path& rawFilePath);

    /**
    * Loads a raw volume file using provided metadata.
    *
    * The .raw format produced by pvm2raw contains no header - it's pure binary
    * voxel data. Metadata must be provided externally via the metadata parameter.
    *
    * This overload is useful when metadata is already known or comes from a
    * different source than a .dat file.
    *
    * @param rawFilePath Path to the .raw file.
    * @param metadata Volume metadata (dimensions, components, bit depth, scaling).
    * @return VolumeLoadingResult containing VolumeData on success, or VolumeLoadingError on failure.
    *
    * @see VolumeData for the loaded volume structure.
    * @see VolumeMetadata for metadata format.
    * @see VolumeLoadingResult for the result type.
    */
    VolumeLoadingResult LoadVolumeRaw(const std::filesystem::path& rawFilePath, const VolumeMetadata& metadata);

}

#endif
