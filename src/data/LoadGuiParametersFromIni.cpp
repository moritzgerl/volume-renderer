#include <data/LoadGuiParametersFromIni.h>
#include <data/GetGuiParametersKey.h>
#include <data/IniFileSection.h>
#include <gui/MakeGuiParameters.h>

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

std::expected<GuiParameters, Data::GuiParametersLoadingError> Data::LoadGuiParametersFromIni(const std::filesystem::path& iniFilePath)
{
    if (!std::filesystem::exists(iniFilePath))
    {
        return std::unexpected(GuiParametersLoadingError::FileNotFound);
    }

    std::ifstream file(iniFilePath);
    if (!file.is_open())
    {
        return std::unexpected(GuiParametersLoadingError::CannotOpenFile);
    }

    GuiParameters guiParameters = Factory::MakeGuiParameters();
    guiParameters.transferFunction.numActivePoints = 0;

    std::string line;
    IniFileSection currentSection = IniFileSection::None;
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
                currentSection = IniFileSection::GuiParameters;
            }
            else if (line == "[TransferFunction]")
            {
                currentSection = IniFileSection::TransferFunction;
            }
            else if (line == "[Camera]")
            {
                currentSection = IniFileSection::Camera;
            }
            else if (line == "[SSAO]")
            {
                currentSection = IniFileSection::SSAO;
            }
            else if (line == "[DirectionalLight]")
            {
                currentSection = IniFileSection::DirectionalLight;
            }
            else if (line == "[Rendering]")
            {
                currentSection = IniFileSection::Rendering;
            }
            else
            {
                // Try parsing Point section
                int pointIndex = ParsePointSection(line);
                if (pointIndex >= 0 && pointIndex < static_cast<int>(TransferFunction::maxControlPoints))
                {
                    currentSection = IniFileSection::TransferFunctionPoint;
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
                        currentSection = IniFileSection::PointLight;
                        currentPointLightIndex = pointLightIndex;
                    }
                    else
                    {
                        currentSection = IniFileSection::None;
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

        GuiParametersKey key = GetGuiParametersKey(keyString);

        switch (currentSection)
        {
            case IniFileSection::TransferFunctionPoint:
            {
                if (currentPointIndex < 0)
                {
                    break;
                }

                TransferFunctionControlPoint& point = guiParameters.transferFunction.controlPoints[currentPointIndex];

                switch (key)
                {
                    case GuiParametersKey::Value:
                        if (!ParseValue(valueString, point.value))
                        {
                            return std::unexpected(GuiParametersLoadingError::ParseError);
                        }
                        break;
                    case GuiParametersKey::ColorR:
                        if (!ParseValue(valueString, point.color.r))
                        {
                            return std::unexpected(GuiParametersLoadingError::ParseError);
                        }
                        break;
                    case GuiParametersKey::ColorG:
                        if (!ParseValue(valueString, point.color.g))
                        {
                            return std::unexpected(GuiParametersLoadingError::ParseError);
                        }
                        break;
                    case GuiParametersKey::ColorB:
                        if (!ParseValue(valueString, point.color.b))
                        {
                            return std::unexpected(GuiParametersLoadingError::ParseError);
                        }
                        break;
                    case GuiParametersKey::Opacity:
                        if (!ParseValue(valueString, point.opacity))
                        {
                            return std::unexpected(GuiParametersLoadingError::ParseError);
                        }
                        break;
                    default:
                        break;
                }
                break;
            }

            case IniFileSection::Camera:
            {
                switch (key)
                {
                    case GuiParametersKey::InvertYAxis:
                    {
                        int value;
                        if (!ParseValue(valueString, value))
                        {
                            return std::unexpected(GuiParametersLoadingError::ParseError);
                        }
                        guiParameters.trackballInvertYAxis = (value != 0);
                        break;
                    }
                    case GuiParametersKey::Sensitivity:
                        if (!ParseValue(valueString, guiParameters.trackballSensitivity))
                        {
                            return std::unexpected(GuiParametersLoadingError::ParseError);
                        }
                        break;
                    default:
                        break;
                }
                break;
            }

            case IniFileSection::SSAO:
            {
                switch (key)
                {
                    case GuiParametersKey::KernelSize:
                        if (!ParseValue(valueString, guiParameters.ssaoKernelSize))
                        {
                            return std::unexpected(GuiParametersLoadingError::ParseError);
                        }
                        break;
                    case GuiParametersKey::NoiseSize:
                        if (!ParseValue(valueString, guiParameters.ssaoNoiseSize))
                        {
                            return std::unexpected(GuiParametersLoadingError::ParseError);
                        }
                        break;
                    case GuiParametersKey::Radius:
                        if (!ParseValue(valueString, guiParameters.ssaoRadius))
                        {
                            return std::unexpected(GuiParametersLoadingError::ParseError);
                        }
                        break;
                    case GuiParametersKey::Bias:
                        if (!ParseValue(valueString, guiParameters.ssaoBias))
                        {
                            return std::unexpected(GuiParametersLoadingError::ParseError);
                        }
                        break;
                    case GuiParametersKey::Enable:
                    {
                        int value;
                        if (!ParseValue(valueString, value))
                        {
                            return std::unexpected(GuiParametersLoadingError::ParseError);
                        }
                        guiParameters.enableSsao = (value != 0);
                        break;
                    }
                    default:
                        break;
                }
                break;
            }

            case IniFileSection::DirectionalLight:
            {
                DirectionalLight& light = guiParameters.directionalLight;

                switch (key)
                {
                    case GuiParametersKey::DirectionX:
                        if (!ParseValue(valueString, light.direction.x))
                        {
                            return std::unexpected(GuiParametersLoadingError::ParseError);
                        }
                        break;
                    case GuiParametersKey::DirectionY:
                        if (!ParseValue(valueString, light.direction.y))
                        {
                            return std::unexpected(GuiParametersLoadingError::ParseError);
                        }
                        break;
                    case GuiParametersKey::DirectionZ:
                        if (!ParseValue(valueString, light.direction.z))
                        {
                            return std::unexpected(GuiParametersLoadingError::ParseError);
                        }
                        break;
                    case GuiParametersKey::AmbientR:
                        if (!ParseValue(valueString, light.ambient.r))
                        {
                            return std::unexpected(GuiParametersLoadingError::ParseError);
                        }
                        break;
                    case GuiParametersKey::AmbientG:
                        if (!ParseValue(valueString, light.ambient.g))
                        {
                            return std::unexpected(GuiParametersLoadingError::ParseError);
                        }
                        break;
                    case GuiParametersKey::AmbientB:
                        if (!ParseValue(valueString, light.ambient.b))
                        {
                            return std::unexpected(GuiParametersLoadingError::ParseError);
                        }
                        break;
                    case GuiParametersKey::DiffuseR:
                        if (!ParseValue(valueString, light.diffuse.r))
                        {
                            return std::unexpected(GuiParametersLoadingError::ParseError);
                        }
                        break;
                    case GuiParametersKey::DiffuseG:
                        if (!ParseValue(valueString, light.diffuse.g))
                        {
                            return std::unexpected(GuiParametersLoadingError::ParseError);
                        }
                        break;
                    case GuiParametersKey::DiffuseB:
                        if (!ParseValue(valueString, light.diffuse.b))
                        {
                            return std::unexpected(GuiParametersLoadingError::ParseError);
                        }
                        break;
                    case GuiParametersKey::SpecularR:
                        if (!ParseValue(valueString, light.specular.r))
                        {
                            return std::unexpected(GuiParametersLoadingError::ParseError);
                        }
                        break;
                    case GuiParametersKey::SpecularG:
                        if (!ParseValue(valueString, light.specular.g))
                        {
                            return std::unexpected(GuiParametersLoadingError::ParseError);
                        }
                        break;
                    case GuiParametersKey::SpecularB:
                        if (!ParseValue(valueString, light.specular.b))
                        {
                            return std::unexpected(GuiParametersLoadingError::ParseError);
                        }
                        break;
                    case GuiParametersKey::Intensity:
                        if (!ParseValue(valueString, light.intensity))
                        {
                            return std::unexpected(GuiParametersLoadingError::ParseError);
                        }
                        break;
                    default:
                        break;
                }
                break;
            }

            case IniFileSection::PointLight:
            {
                if (currentPointLightIndex < 0)
                {
                    break;
                }

                PointLight& light = guiParameters.pointLights[currentPointLightIndex];

                switch (key)
                {
                    case GuiParametersKey::PositionX:
                        if (!ParseValue(valueString, light.position.x))
                        {
                            return std::unexpected(GuiParametersLoadingError::ParseError);
                        }
                        break;
                    case GuiParametersKey::PositionY:
                        if (!ParseValue(valueString, light.position.y))
                        {
                            return std::unexpected(GuiParametersLoadingError::ParseError);
                        }
                        break;
                    case GuiParametersKey::PositionZ:
                        if (!ParseValue(valueString, light.position.z))
                        {
                            return std::unexpected(GuiParametersLoadingError::ParseError);
                        }
                        break;
                    case GuiParametersKey::AmbientR:
                        if (!ParseValue(valueString, light.ambient.r))
                        {
                            return std::unexpected(GuiParametersLoadingError::ParseError);
                        }
                        break;
                    case GuiParametersKey::AmbientG:
                        if (!ParseValue(valueString, light.ambient.g))
                        {
                            return std::unexpected(GuiParametersLoadingError::ParseError);
                        }
                        break;
                    case GuiParametersKey::AmbientB:
                        if (!ParseValue(valueString, light.ambient.b))
                        {
                            return std::unexpected(GuiParametersLoadingError::ParseError);
                        }
                        break;
                    case GuiParametersKey::DiffuseR:
                        if (!ParseValue(valueString, light.diffuse.r))
                        {
                            return std::unexpected(GuiParametersLoadingError::ParseError);
                        }
                        break;
                    case GuiParametersKey::DiffuseG:
                        if (!ParseValue(valueString, light.diffuse.g))
                        {
                            return std::unexpected(GuiParametersLoadingError::ParseError);
                        }
                        break;
                    case GuiParametersKey::DiffuseB:
                        if (!ParseValue(valueString, light.diffuse.b))
                        {
                            return std::unexpected(GuiParametersLoadingError::ParseError);
                        }
                        break;
                    case GuiParametersKey::SpecularR:
                        if (!ParseValue(valueString, light.specular.r))
                        {
                            return std::unexpected(GuiParametersLoadingError::ParseError);
                        }
                        break;
                    case GuiParametersKey::SpecularG:
                        if (!ParseValue(valueString, light.specular.g))
                        {
                            return std::unexpected(GuiParametersLoadingError::ParseError);
                        }
                        break;
                    case GuiParametersKey::SpecularB:
                        if (!ParseValue(valueString, light.specular.b))
                        {
                            return std::unexpected(GuiParametersLoadingError::ParseError);
                        }
                        break;
                    case GuiParametersKey::Intensity:
                        if (!ParseValue(valueString, light.intensity))
                        {
                            return std::unexpected(GuiParametersLoadingError::ParseError);
                        }
                        break;
                    default:
                        break;
                }
                break;
            }

            case IniFileSection::Rendering:
            {
                switch (key)
                {
                    case GuiParametersKey::ShowLightSources:
                    {
                        int value;
                        if (!ParseValue(valueString, value))
                        {
                            return std::unexpected(GuiParametersLoadingError::ParseError);
                        }
                        guiParameters.showLightSources = (value != 0);
                        break;
                    }
                    case GuiParametersKey::DensityMultiplier:
                        if (!ParseValue(valueString, guiParameters.raycastingDensityMultiplier))
                        {
                            return std::unexpected(GuiParametersLoadingError::ParseError);
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

    return guiParameters;
}
