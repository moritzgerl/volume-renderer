/**
* \file VolumeMetadataKey.h
*
* \brief Enumeration of metadata field identifiers for volume files.
*/

#ifndef VOLUME_METADATA_KEY_H
#define VOLUME_METADATA_KEY_H

namespace VolumeData
{
    /**
    * \enum VolumeMetadataKey
    *
    * \brief Identifies metadata fields in .dat volume metadata files.
    *
    * Each enum value corresponds to a key in the .dat metadata file
    * that accompanies a .raw volume file. These keys map to properties
    * in the VolumeMetadata class.
    *
    * The metadata file contains key-value pairs like "Width = 512",
    * "BitsPerComponent = 8", etc.
    *
    * @see VolumeMetadata for the metadata structure.
    * @see LoadVolumeRaw for metadata file parsing.
    * @see GetVolumeMetadataKey for converting strings to keys.
    */
    enum class VolumeMetadataKey
    {
        Width,              /**< Volume width in voxels. */
        Height,             /**< Volume height in voxels. */
        Depth,              /**< Volume depth in voxels. */
        Components,         /**< Number of components per voxel. */
        BitsPerComponent,   /**< Bits per component (8 or 16). */
        ScaleX,             /**< Physical spacing scale factor in X direction. */
        ScaleY,             /**< Physical spacing scale factor in Y direction. */
        ScaleZ,             /**< Physical spacing scale factor in Z direction. */
        Unknown             /**< Unrecognized metadata key. */
    };
}

#endif
