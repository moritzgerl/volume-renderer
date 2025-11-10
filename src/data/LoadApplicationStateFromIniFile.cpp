#include <data/LoadApplicationStateFromIniFile.h>
#include <data/GetApplicationStateIniFileKey.h>
#include <data/ApplicationStateIniFileSection.h>
#include <camera/CameraParameters.h>
#include <camera/MakeDefaultCameraParameters.h>
#include <gui/GuiParameters.h>
#include <gui/MakeDefaultGuiParameters.h>


#include <charconv>
#include <fstream>
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

    /// Parse a Point section header like "[Point0]" and return the index
    /// Returns -1 if not a valid point section
    int ParsePointSection(const std::string& line)
    {
        if (line.size() < 8 || line.substr(0, 6) != "[Point" || line.back() != ']')
        {
            return -1;
        }

        std::string indexStr = line.substr(6, line.size() - 7);
        int index;
        if (!ParseValue(indexStr, index))
        {
            return -1;
        }

        return index;
    }

    /// Parse a PointLight section header like "[PointLight0]" and return the index
    /// Returns -1 if not a valid point light section
    int ParsePointLightSection(const std::string& line)
    {
        if (line.size() < 13 || line.substr(0, 11) != "[PointLight" || line.back() != ']')
        {
            return -1;
        }

        std::string indexStr = line.substr(11, line.size() - 12);
        int index;
        if (!ParseValue(indexStr, index))
        {
            return -1;
        }

        return index;
    }
}

std::expected<Data::ApplicationState, Data::ApplicationStateIniFileLoadingError> Data::LoadApplicationStateFromIniFile(const std::filesystem::path& iniFilePath)
{
    if (!std::filesystem::exists(iniFilePath))
    {
        return std::unexpected(ApplicationStateIniFileLoadingError::FileNotFound);
    }

    std::ifstream file(iniFilePath);
    if (!file.is_open())
    {
        return std::unexpected(ApplicationStateIniFileLoadingError::CannotOpenFile);
    }

    CameraParameters cameraParameters = Factory::MakeDefaultCameraParameters();
    GuiParameters guiParameters = Factory::MakeDefaultGuiParameters();
    
    guiParameters.transferFunction.numActivePoints = 0;

    std::string line;
    ApplicationStateIniFileSection currentSection = ApplicationStateIniFileSection::None;
    int currentPointIndex = -1;
    int currentPointLightIndex = -1;

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
            if (line == "[GuiParameters]")
            {
                currentSection = ApplicationStateIniFileSection::GuiParameters;
            }
            else if (line == "[TransferFunction]")
            {
                currentSection = ApplicationStateIniFileSection::TransferFunction;
            }
            else if (line == "[Camera]")
            {
                currentSection = ApplicationStateIniFileSection::Camera;
            }
            else if (line == "[SSAO]")
            {
                currentSection = ApplicationStateIniFileSection::SSAO;
            }
            else if (line == "[DirectionalLight]")
            {
                currentSection = ApplicationStateIniFileSection::DirectionalLight;
            }
            else if (line == "[Rendering]")
            {
                currentSection = ApplicationStateIniFileSection::Rendering;
            }
            else
            {
                // Try parsing Point section
                int pointIndex = ParsePointSection(line);
                if (pointIndex >= 0 && pointIndex < static_cast<int>(TransferFunction::maxControlPoints))
                {
                    currentSection = ApplicationStateIniFileSection::TransferFunctionPoint;
                    currentPointIndex = pointIndex;
                    if (static_cast<size_t>(pointIndex) >= guiParameters.transferFunction.numActivePoints)
                    {
                        guiParameters.transferFunction.numActivePoints = static_cast<size_t>(pointIndex) + 1;
                    }
                }
                else
                {
                    // Try parsing PointLight section
                    int pointLightIndex = ParsePointLightSection(line);
                    if (pointLightIndex >= 0 && pointLightIndex < static_cast<int>(guiParameters.pointLights.size()))
                    {
                        currentSection = ApplicationStateIniFileSection::PointLight;
                        currentPointLightIndex = pointLightIndex;
                    }
                    else
                    {
                        currentSection = ApplicationStateIniFileSection::None;
                    }
                }
            }
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

        ApplicationStateIniFileKey key = GetApplicationStateIniFileKey(keyString);

        switch (currentSection)
        {
            case ApplicationStateIniFileSection::TransferFunctionPoint:
            {
                if (currentPointIndex < 0)
                {
                    break;
                }

                TransferFunctionControlPoint& point = guiParameters.transferFunction.controlPoints[currentPointIndex];

                switch (key)
                {
                    case ApplicationStateIniFileKey::Value:
                        if (!ParseValue(valueString, point.value))
                        {
                            return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
                        }
                        break;
                    case ApplicationStateIniFileKey::ColorR:
                        if (!ParseValue(valueString, point.color.r))
                        {
                            return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
                        }
                        break;
                    case ApplicationStateIniFileKey::ColorG:
                        if (!ParseValue(valueString, point.color.g))
                        {
                            return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
                        }
                        break;
                    case ApplicationStateIniFileKey::ColorB:
                        if (!ParseValue(valueString, point.color.b))
                        {
                            return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
                        }
                        break;
                    case ApplicationStateIniFileKey::Opacity:
                        if (!ParseValue(valueString, point.opacity))
                        {
                            return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
                        }
                        break;
                    default:
                        break;
                }
                break;
            }

            case ApplicationStateIniFileSection::Camera:
            {
                switch (key)
                {
                    case ApplicationStateIniFileKey::InvertYAxis:
                    {
                        int value;
                        if (!ParseValue(valueString, value))
                        {
                            return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
                        }
                        guiParameters.trackballInvertYAxis = (value != 0);
                        break;
                    }
                    case ApplicationStateIniFileKey::Sensitivity:
                        if (!ParseValue(valueString, guiParameters.trackballSensitivity))
                        {
                            return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
                        }
                        break;
                    default:
                        break;
                }
                break;
            }

            case ApplicationStateIniFileSection::SSAO:
            {
                switch (key)
                {
                    case ApplicationStateIniFileKey::KernelSize:
                        if (!ParseValue(valueString, guiParameters.ssaoKernelSize))
                        {
                            return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
                        }
                        break;
                    case ApplicationStateIniFileKey::NoiseSize:
                        if (!ParseValue(valueString, guiParameters.ssaoNoiseSize))
                        {
                            return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
                        }
                        break;
                    case ApplicationStateIniFileKey::Radius:
                        if (!ParseValue(valueString, guiParameters.ssaoRadius))
                        {
                            return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
                        }
                        break;
                    case ApplicationStateIniFileKey::Bias:
                        if (!ParseValue(valueString, guiParameters.ssaoBias))
                        {
                            return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
                        }
                        break;
                    case ApplicationStateIniFileKey::Enable:
                    {
                        int value;
                        if (!ParseValue(valueString, value))
                        {
                            return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
                        }
                        guiParameters.enableSsao = (value != 0);
                        break;
                    }
                    default:
                        break;
                }
                break;
            }

            case ApplicationStateIniFileSection::DirectionalLight:
            {
                DirectionalLight& light = guiParameters.directionalLight;

                switch (key)
                {
                    case ApplicationStateIniFileKey::DirectionX:
                        if (!ParseValue(valueString, light.direction.x))
                        {
                            return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
                        }
                        break;
                    case ApplicationStateIniFileKey::DirectionY:
                        if (!ParseValue(valueString, light.direction.y))
                        {
                            return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
                        }
                        break;
                    case ApplicationStateIniFileKey::DirectionZ:
                        if (!ParseValue(valueString, light.direction.z))
                        {
                            return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
                        }
                        break;
                    case ApplicationStateIniFileKey::AmbientR:
                        if (!ParseValue(valueString, light.ambient.r))
                        {
                            return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
                        }
                        break;
                    case ApplicationStateIniFileKey::AmbientG:
                        if (!ParseValue(valueString, light.ambient.g))
                        {
                            return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
                        }
                        break;
                    case ApplicationStateIniFileKey::AmbientB:
                        if (!ParseValue(valueString, light.ambient.b))
                        {
                            return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
                        }
                        break;
                    case ApplicationStateIniFileKey::DiffuseR:
                        if (!ParseValue(valueString, light.diffuse.r))
                        {
                            return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
                        }
                        break;
                    case ApplicationStateIniFileKey::DiffuseG:
                        if (!ParseValue(valueString, light.diffuse.g))
                        {
                            return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
                        }
                        break;
                    case ApplicationStateIniFileKey::DiffuseB:
                        if (!ParseValue(valueString, light.diffuse.b))
                        {
                            return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
                        }
                        break;
                    case ApplicationStateIniFileKey::SpecularR:
                        if (!ParseValue(valueString, light.specular.r))
                        {
                            return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
                        }
                        break;
                    case ApplicationStateIniFileKey::SpecularG:
                        if (!ParseValue(valueString, light.specular.g))
                        {
                            return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
                        }
                        break;
                    case ApplicationStateIniFileKey::SpecularB:
                        if (!ParseValue(valueString, light.specular.b))
                        {
                            return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
                        }
                        break;
                    case ApplicationStateIniFileKey::Intensity:
                        if (!ParseValue(valueString, light.intensity))
                        {
                            return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
                        }
                        break;
                    default:
                        break;
                }
                break;
            }

            case ApplicationStateIniFileSection::PointLight:
            {
                if (currentPointLightIndex < 0)
                {
                    break;
                }

                PointLight& light = guiParameters.pointLights[currentPointLightIndex];

                switch (key)
                {
                    case ApplicationStateIniFileKey::PositionX:
                        if (!ParseValue(valueString, light.position.x))
                        {
                            return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
                        }
                        break;
                    case ApplicationStateIniFileKey::PositionY:
                        if (!ParseValue(valueString, light.position.y))
                        {
                            return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
                        }
                        break;
                    case ApplicationStateIniFileKey::PositionZ:
                        if (!ParseValue(valueString, light.position.z))
                        {
                            return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
                        }
                        break;
                    case ApplicationStateIniFileKey::AmbientR:
                        if (!ParseValue(valueString, light.ambient.r))
                        {
                            return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
                        }
                        break;
                    case ApplicationStateIniFileKey::AmbientG:
                        if (!ParseValue(valueString, light.ambient.g))
                        {
                            return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
                        }
                        break;
                    case ApplicationStateIniFileKey::AmbientB:
                        if (!ParseValue(valueString, light.ambient.b))
                        {
                            return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
                        }
                        break;
                    case ApplicationStateIniFileKey::DiffuseR:
                        if (!ParseValue(valueString, light.diffuse.r))
                        {
                            return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
                        }
                        break;
                    case ApplicationStateIniFileKey::DiffuseG:
                        if (!ParseValue(valueString, light.diffuse.g))
                        {
                            return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
                        }
                        break;
                    case ApplicationStateIniFileKey::DiffuseB:
                        if (!ParseValue(valueString, light.diffuse.b))
                        {
                            return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
                        }
                        break;
                    case ApplicationStateIniFileKey::SpecularR:
                        if (!ParseValue(valueString, light.specular.r))
                        {
                            return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
                        }
                        break;
                    case ApplicationStateIniFileKey::SpecularG:
                        if (!ParseValue(valueString, light.specular.g))
                        {
                            return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
                        }
                        break;
                    case ApplicationStateIniFileKey::SpecularB:
                        if (!ParseValue(valueString, light.specular.b))
                        {
                            return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
                        }
                        break;
                    case ApplicationStateIniFileKey::Intensity:
                        if (!ParseValue(valueString, light.intensity))
                        {
                            return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
                        }
                        break;
                    default:
                        break;
                }
                break;
            }

            case ApplicationStateIniFileSection::Rendering:
            {
                switch (key)
                {
                    case ApplicationStateIniFileKey::ShowLightSources:
                    {
                        int value;
                        if (!ParseValue(valueString, value))
                        {
                            return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
                        }
                        guiParameters.showLightSources = (value != 0);
                        break;
                    }
                    case ApplicationStateIniFileKey::DensityMultiplier:
                        if (!ParseValue(valueString, guiParameters.raycastingDensityMultiplier))
                        {
                            return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
                        }
                        break;
                    default:
                        break;
                }
                break;
            }

            default:
                break;
        }
    }

    return ApplicationState
    {
        .cameraParameters = cameraParameters,
        .guiParameters = guiParameters
    };
}
