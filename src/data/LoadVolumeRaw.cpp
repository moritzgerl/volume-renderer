#include <data/LoadVolumeRaw.h>
#include <data/GetVolumeMetadataKey.h>

#include <charconv>
#include <fstream>
#include <sstream>
#include <string>

namespace
{
    /// Parse a value from a string using std::from_chars
    /// Returns true on success, false on parse error
    template<typename T>
    bool ParseValue(const std::string& str, T& out)
    {
        auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), out);
        return ec == std::errc{};
    }

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

            std::string keyString = line.substr(0, equalPos);
            std::string valueString = line.substr(equalPos + 1);

            // Trim key and value
            keyString.erase(0, keyString.find_first_not_of(" \t"));
            keyString.erase(keyString.find_last_not_of(" \t") + 1);
            valueString.erase(0, valueString.find_first_not_of(" \t"));
            valueString.erase(valueString.find_last_not_of(" \t") + 1);

            switch (Data::GetVolumeMetadataKey(keyString))
            {
                case Data::VolumeMetadataKey::Width:
                {
                    size_t width;
                    if (!ParseValue(valueString, width))
                    {
                        return std::unexpected(Data::VolumeLoadingError::MetadataParseError);
                    }
                    metadata.SetWidth(static_cast<uint32_t>(width));
                    break;
                }
                case Data::VolumeMetadataKey::Height:
                {
                    size_t height;
                    if (!ParseValue(valueString, height))
                    {
                        return std::unexpected(Data::VolumeLoadingError::MetadataParseError);
                    }
                    metadata.SetHeight(static_cast<uint32_t>(height));
                    break;
                }
                case Data::VolumeMetadataKey::Depth:
                {
                    size_t depth;
                    if (!ParseValue(valueString, depth))
                    {
                        return std::unexpected(Data::VolumeLoadingError::MetadataParseError);
                    }
                    metadata.SetDepth(static_cast<uint32_t>(depth));
                    break;
                }
                case Data::VolumeMetadataKey::Components:
                {
                    size_t components;
                    if (!ParseValue(valueString, components))
                    {
                        return std::unexpected(Data::VolumeLoadingError::MetadataParseError);
                    }
                    metadata.SetComponents(static_cast<uint32_t>(components));
                    break;
                }
                case Data::VolumeMetadataKey::BitsPerComponent:
                {
                    size_t bitsPerComponent;
                    if (!ParseValue(valueString, bitsPerComponent))
                    {
                        return std::unexpected(Data::VolumeLoadingError::MetadataParseError);
                    }
                    metadata.SetBitsPerComponent(static_cast<uint32_t>(bitsPerComponent));
                    break;
                }
                case Data::VolumeMetadataKey::ScaleX:
                {
                    float scaleX;
                    if (!ParseValue(valueString, scaleX))
                    {
                        return std::unexpected(Data::VolumeLoadingError::MetadataParseError);
                    }
                    metadata.SetScaleX(scaleX);
                    break;
                }
                case Data::VolumeMetadataKey::ScaleY:
                {
                    float scaleY;
                    if (!ParseValue(valueString, scaleY))
                    {
                        return std::unexpected(Data::VolumeLoadingError::MetadataParseError);
                    }
                    metadata.SetScaleY(scaleY);
                    break;
                }
                case Data::VolumeMetadataKey::ScaleZ:
                {
                    float scaleZ;
                    if (!ParseValue(valueString, scaleZ))
                    {
                        return std::unexpected(Data::VolumeLoadingError::MetadataParseError);
                    }
                    metadata.SetScaleZ(scaleZ);
                    break;
                }
                case Data::VolumeMetadataKey::Unknown:
                    // Ignore unknown keys
                    break;
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

Data::VolumeLoadingResult Data::LoadVolumeRaw(const std::filesystem::path& rawFilePath)
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

Data::VolumeLoadingResult Data::LoadVolumeRaw(const std::filesystem::path& rawFilePath, const VolumeMetadata& metadata)
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
