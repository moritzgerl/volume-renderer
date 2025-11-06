#include <data/LoadVolumeRaw.h>
#include <fstream>
#include <sstream>
#include <string>

namespace
{

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
    std::expected<void, Data::VolumeLoadingError> LoadMetadataFromIni(const std::filesystem::path& iniFilePath, Data::VolumeMetadata& metadata)
    {
        if (!std::filesystem::exists(iniFilePath))
        {
            return std::unexpected(Data::VolumeLoadingError::MetadataFileNotFound);
        }

        std::ifstream file(iniFilePath);
        if (!file.is_open())
        {
            return std::unexpected(Data::VolumeLoadingError::CannotOpenMetadataFile);
        }

        std::string line;
        bool inVolumeSection = false;

        while (std::getline(file, line))
        {
            // Trim whitespace
            line.erase(0, line.find_first_not_of(" \t\r\n"));
            line.erase(line.find_last_not_of(" \t\r\n") + 1);

            // Skip empty lines and comments
            if (line.empty() || line[0] == '#' || line[0] == ';')
            {
                continue;
            }

            // Check for section header
            if (line[0] == '[')
            {
                inVolumeSection = (line == "[Volume]");
                continue;
            }

            if (!inVolumeSection)
            {
                continue;
            }

            // Parse key=value pairs
            size_t equalPos = line.find('=');
            if (equalPos == std::string::npos)
            {
                continue;
            }

            std::string key = line.substr(0, equalPos);
            std::string value = line.substr(equalPos + 1);

            // Trim key and value
            key.erase(0, key.find_first_not_of(" \t"));
            key.erase(key.find_last_not_of(" \t") + 1);
            value.erase(0, value.find_first_not_of(" \t"));
            value.erase(value.find_last_not_of(" \t") + 1);

            // TODO remove exceptions
            try
            {
                if (key == "Width")
                {
                    metadata.SetWidth(std::stoul(value));
                }
                else if (key == "Height")
                {
                    metadata.SetHeight(std::stoul(value));
                }
                else if (key == "Depth")
                {
                    metadata.SetDepth(std::stoul(value));
                }
                else if (key == "Components")
                {
                    metadata.SetComponents(std::stoul(value));
                }
                else if (key == "BitsPerComponent")
                {
                    metadata.SetBitsPerComponent(std::stoul(value));
                }
                else if (key == "ScaleX")
                {
                    metadata.SetScaleX(std::stof(value));
                }
                else if (key == "ScaleY")
                {
                    metadata.SetScaleY(std::stof(value));
                }
                else if (key == "ScaleZ")
                {
                    metadata.SetScaleZ(std::stof(value));
                }
            }
            catch (const std::exception&)
            {
                return std::unexpected(Data::VolumeLoadingError::MetadataParseError);
            }
        }

        if (!metadata.IsValid())
        {
            return std::unexpected(Data::VolumeLoadingError::InvalidMetadata);
        }

        return {};
    }

    /// Load raw binary data from file
    std::expected<void, Data::VolumeLoadingError> LoadRawData(const std::filesystem::path& rawFilePath, Data::VolumeData& volumeData)
    {
        if (!std::filesystem::exists(rawFilePath))
        {
            return std::unexpected(Data::VolumeLoadingError::RawFileNotFound);
        }

        const size_t expectedSize = volumeData.GetMetadata().GetTotalSizeInBytes();
        const size_t fileSize = std::filesystem::file_size(rawFilePath);

        if (fileSize != expectedSize)
        {
            return std::unexpected(Data::VolumeLoadingError::FileSizeMismatch);
        }

        std::ifstream file(rawFilePath, std::ios::binary);
        if (!file.is_open())
        {
            return std::unexpected(Data::VolumeLoadingError::CannotOpenRawFile);
        }

        volumeData.AllocateData(expectedSize);
        file.read(reinterpret_cast<char*>(volumeData.GetDataPtr()), expectedSize);

        if (!file.good())
        {
            return std::unexpected(Data::VolumeLoadingError::ReadError);
        }

        return {};
    }

} // anonymous namespace

std::expected<std::unique_ptr<Data::VolumeData>, Data::VolumeLoadingError> Data::LoadVolumeRaw(const std::filesystem::path& rawFilePath)
{
    // Load metadata from .ini file
    std::filesystem::path iniFilePath = rawFilePath;
    iniFilePath.replace_extension(".ini");

    VolumeMetadata metadata;
    if (auto result = LoadMetadataFromIni(iniFilePath, metadata); !result)
    {
        return std::unexpected(result.error());
    }

    return LoadVolumeRaw(rawFilePath, metadata);
}

std::expected<std::unique_ptr<Data::VolumeData>, Data::VolumeLoadingError> Data::LoadVolumeRaw(const std::filesystem::path& rawFilePath, const VolumeMetadata& metadata)
{
    if (!metadata.IsValid())
    {
        return std::unexpected(VolumeLoadingError::InvalidMetadata);
    }

    auto volumeData = std::make_unique<VolumeData>(metadata);

    if (auto result = LoadRawData(rawFilePath, *volumeData); !result)
    {
        return std::unexpected(result.error());
    }

    if (!volumeData->IsValid())
    {
        return std::unexpected(VolumeLoadingError::InvalidVolumeData);
    }

    return volumeData;
}
