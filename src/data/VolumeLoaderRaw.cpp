#include <data/VolumeLoaderRaw.h>
#include <fstream>
#include <sstream>
#include <string>


std::unique_ptr<Data::VolumeData> Data::VolumeLoaderRaw::Load(const std::filesystem::path& rawFilePath)
{
    // Load metadata from .ini file
    std::filesystem::path iniFilePath = rawFilePath;
    iniFilePath.replace_extension(".ini");

    VolumeMetadata metadata;
    if (!LoadMetadataFromIni(iniFilePath, metadata))
    {
        return nullptr;
    }

    return Load(rawFilePath, metadata);
}

std::unique_ptr<Data::VolumeData> Data::VolumeLoaderRaw::Load(const std::filesystem::path& rawFilePath,
                                                   const VolumeMetadata& metadata)
{
    if (!metadata.IsValid())
    {
        return nullptr;
    }

    auto volumeData = std::make_unique<VolumeData>(metadata);

    if (!LoadRawData(rawFilePath, *volumeData))
    {
        return nullptr;
    }

    if (!volumeData->IsValid())
    {
        return nullptr;
    }

    return volumeData;
}

bool Data::VolumeLoaderRaw::LoadMetadataFromIni(const std::filesystem::path& iniFilePath,
                                         VolumeMetadata& metadata)
{
    if (!std::filesystem::exists(iniFilePath))
    {
        return false;
    }

    std::ifstream file(iniFilePath);
    if (!file.is_open())
    {
        return false;
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
            return false;
        }
    }

    return metadata.IsValid();
}

bool Data::VolumeLoaderRaw::LoadRawData(const std::filesystem::path& rawFilePath,
                                 VolumeData& volumeData)
{
    if (!std::filesystem::exists(rawFilePath))
    {
        return false;
    }

    const size_t expectedSize = volumeData.GetMetadata().GetTotalSizeInBytes();
    const size_t fileSize = std::filesystem::file_size(rawFilePath);

    if (fileSize != expectedSize)
    {
        return false;
    }

    std::ifstream file(rawFilePath, std::ios::binary);
    if (!file.is_open())
    {
        return false;
    }

    volumeData.AllocateData(expectedSize);
    file.read(reinterpret_cast<char*>(volumeData.GetDataPtr()), expectedSize);

    return file.good();
}
