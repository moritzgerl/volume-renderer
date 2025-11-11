// TODO clean up includes
#include <persistence/LoadApplicationStateFromIniFile.h>
#include <persistence/ApplicationStateIniFileSection.h>
#include <persistence/GetApplicationStateIniFileKey.h>
#include <persistence/ParseCameraParameter.h>
#include <persistence/ParseGuiParameter.h>
#include <persistence/ParseElementIndex.h>
#include <persistence/ParseKeyValuePair.h>
#include <persistence/ParseSectionHeader.h>
#include <persistence/ParseTransferFunctionControlPoint.h>
#include <persistence/KeyValuePair.h>
#include <camera/CameraParameters.h>
#include <camera/MakeDefaultCameraParameters.h>
#include <gui/GuiParameters.h>
#include <gui/MakeDefaultGuiParameters.h>

#include <fstream>
#include <string>

namespace
{
    void TrimWhitespaceInLine(std::string& line)
    {
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);
    }

    bool DoesLineContainData(const std::string& line)
    {
        return !line.empty()
            && line[0] != '#'
            && line[0] != ';';
    }

    bool IsSectionHeader(const std::string& line)
    {
        return line[0] == '[';
    }

    bool IsArraySection(Persistence::ApplicationStateIniFileSection section)
    {
        return section == Persistence::ApplicationStateIniFileSection::TransferFunctionPoint
            || section == Persistence::ApplicationStateIniFileSection::PointLight;
    }
}

std::expected<Persistence::ApplicationState, Persistence::ApplicationStateIniFileLoadingError> Persistence::LoadApplicationStateFromIniFile(const std::filesystem::path& iniFilePath)
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
    unsigned int currentElementIndex = 0;
    unsigned int maxTransferFunctionPointIndex = 0;
    bool foundTransferFunctionPoint = false;

    while (std::getline(file, line))
    {
        TrimWhitespaceInLine(line);

        if (!DoesLineContainData(line))
        {
            continue;
        }

        if (IsSectionHeader(line))
        {
            currentSection = ParseSectionHeader(line);

            if (IsArraySection(currentSection))
            {
                auto elementIndexParseResult = ParseElementIndex(line, currentSection);

                if (elementIndexParseResult)
                {
                    currentElementIndex = elementIndexParseResult.value();
                }
                else
                {
                    return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
                }
            }

            continue;
        }

        KeyValuePair keyValuePair = ParseKeyValuePair(line);
        const std::string& keyString = keyValuePair.key;
        const std::string& valueString = keyValuePair.value;
        ApplicationStateIniFileKey key = GetApplicationStateIniFileKey(keyString);

        switch (currentSection)
        {
            case ApplicationStateIniFileSection::Camera:
            {
                const bool cameraParameterParseSuccess = ParseCameraParameter(key, valueString, cameraParameters);
                
                if (!cameraParameterParseSuccess)
                {
                    return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
                }
                break;
            }

            case ApplicationStateIniFileSection::TransferFunctionPoint:
            {
                TransferFunctionControlPoint& point = guiParameters.transferFunction.controlPoints[currentElementIndex];

                const bool transferFunctionPointParseSuccess = ParseTransferFunctionControlPoint(key, valueString, point);

                if (!transferFunctionPointParseSuccess)
                {
                    return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
                }

                foundTransferFunctionPoint = true;
                maxTransferFunctionPointIndex = std::max(maxTransferFunctionPointIndex, currentElementIndex);

                break;
            }

            case ApplicationStateIniFileSection::SSAO:
            case ApplicationStateIniFileSection::DirectionalLight:
            case ApplicationStateIniFileSection::PointLight:
            case ApplicationStateIniFileSection::Rendering:
            {
                const bool guiParameterParseSuccess = ParseGuiParameter(
                    currentSection,
                    key,
                    currentElementIndex,
                    valueString,
                    guiParameters);

                if (!guiParameterParseSuccess)
                {
                    return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
                }
                
                break;
            }

            default:
                break;
        }
    }

    if (foundTransferFunctionPoint)
    {
        guiParameters.transferFunction.numActivePoints = maxTransferFunctionPointIndex + 1;
    }

    return ApplicationState
    {
        .cameraParameters = cameraParameters,
        .guiParameters = guiParameters
    };
}
