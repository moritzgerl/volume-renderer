#include <data/LoadSaveStateFromIni.h>
#include <data/GetSaveStateKey.h>

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
}

std::expected<Data::SaveState, Data::SaveStateLoadingError> Data::LoadSaveStateFromIni(const std::filesystem::path& iniFilePath)
{
    if (!std::filesystem::exists(iniFilePath))
    {
        return std::unexpected(SaveStateLoadingError::FileNotFound);
    }

    std::ifstream file(iniFilePath);
    if (!file.is_open())
    {
        return std::unexpected(SaveStateLoadingError::CannotOpenFile);
    }

    SaveState saveState{};
    saveState.transferFunction.numActivePoints = 0;

    std::string line;
    bool inSaveStateSection = false;
    int currentPointIndex = -1;

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
            if (line == "[SaveState]")
            {
                inSaveStateSection = true;
                currentPointIndex = -1;
            }
            else
            {
                int pointIndex = ParsePointSection(line);
                if (pointIndex >= 0 && pointIndex < static_cast<int>(TransferFunction::maxControlPoints))
                {
                    currentPointIndex = pointIndex;
                    if (static_cast<size_t>(pointIndex) >= saveState.transferFunction.numActivePoints)
                    {
                        saveState.transferFunction.numActivePoints = static_cast<size_t>(pointIndex) + 1;
                    }
                }
                else
                {
                    inSaveStateSection = false;
                    currentPointIndex = -1;
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

        // Parse transfer function control point data
        if (currentPointIndex >= 0)
        {
            TransferFunctionControlPoint& point = saveState.transferFunction.controlPoints[currentPointIndex];

            switch (GetSaveStateKey(keyString))
            {
                case SaveStateKey::Value:
                {
                    if (!ParseValue(valueString, point.value))
                    {
                        return std::unexpected(SaveStateLoadingError::ParseError);
                    }
                    break;
                }
                case SaveStateKey::ColorR:
                {
                    if (!ParseValue(valueString, point.color.r))
                    {
                        return std::unexpected(SaveStateLoadingError::ParseError);
                    }
                    break;
                }
                case SaveStateKey::ColorG:
                {
                    if (!ParseValue(valueString, point.color.g))
                    {
                        return std::unexpected(SaveStateLoadingError::ParseError);
                    }
                    break;
                }
                case SaveStateKey::ColorB:
                {
                    if (!ParseValue(valueString, point.color.b))
                    {
                        return std::unexpected(SaveStateLoadingError::ParseError);
                    }
                    break;
                }
                case SaveStateKey::Opacity:
                {
                    if (!ParseValue(valueString, point.opacity))
                    {
                        return std::unexpected(SaveStateLoadingError::ParseError);
                    }
                    break;
                }
                case SaveStateKey::Unknown:
                    // Ignore unknown keys
                    break;
            }
        }
    }

    return saveState;
}
