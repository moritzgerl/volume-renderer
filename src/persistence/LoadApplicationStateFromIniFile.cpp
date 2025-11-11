#include <persistence/LoadApplicationStateFromIniFile.h>
#include <persistence/ApplicationStateIniFileSection.h>
#include <persistence/GetApplicationStateIniFileKey.h>
#include <persistence/KeyValuePair.h>
#include <persistence/ParseCameraParameter.h>
#include <persistence/ParseElementIndex.h>
#include <persistence/ParseGuiParameter.h>
#include <persistence/ParseKeyValuePair.h>
#include <persistence/ParseSectionHeader.h>
#include <persistence/ParseTransferFunctionControlPoint.h>
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
                const auto elementIndexParseResult = ParseElementIndex(line, currentSection);

                if (elementIndexParseResult)
                {
                    currentElementIndex = elementIndexParseResult.value();
                }
                else
                {
                    return std::unexpected(elementIndexParseResult.error());
                }
            }

            continue;
        }

        KeyValuePair keyValuePair = ParseKeyValuePair(line);
        const std::string_view keyString = keyValuePair.key;
        const std::string_view valueString = keyValuePair.value;
        ApplicationStateIniFileKey key = GetApplicationStateIniFileKey(keyString);

        switch (currentSection)
        {
            case ApplicationStateIniFileSection::Camera:
            {
                const auto cameraParameterParseResult = ParseCameraParameter(key, valueString, cameraParameters);

                if (!cameraParameterParseResult)
                {
                    return std::unexpected(cameraParameterParseResult.error());
                }
                break;
            }

            case ApplicationStateIniFileSection::TransferFunctionPoint:
            {
                TransferFunctionControlPoint& point = guiParameters.transferFunction.controlPoints[currentElementIndex];

                const auto transferFunctionPointParseResult = ParseTransferFunctionControlPoint(key, valueString, point);

                if (!transferFunctionPointParseResult)
                {
                    return std::unexpected(transferFunctionPointParseResult.error());
                }

                foundTransferFunctionPoint = true;
                maxTransferFunctionPointIndex = std::max(maxTransferFunctionPointIndex, currentElementIndex);

                break;
            }

            case ApplicationStateIniFileSection::SSAO:
            case ApplicationStateIniFileSection::Trackball:
            case ApplicationStateIniFileSection::DirectionalLight:
            case ApplicationStateIniFileSection::PointLight:
            case ApplicationStateIniFileSection::Rendering:
            {
                const auto guiParameterParseResult = ParseGuiParameter(
                    currentSection,
                    key,
                    currentElementIndex,
                    valueString,
                    guiParameters);

                if (!guiParameterParseResult)
                {
                    return std::unexpected(guiParameterParseResult.error());
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
