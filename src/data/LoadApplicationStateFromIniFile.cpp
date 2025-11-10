// TODO clean up includes
#include <data/LoadApplicationStateFromIniFile.h>
#include <data/ApplicationStateIniFileSection.h>
#include <data/GetApplicationStateIniFileKey.h>
#include <data/ParseCameraParameter.h>
#include <data/ParseGuiParameter.h>
#include <data/ParseElementIndex.h>
#include <data/ParseKeyValuePair.h>
#include <data/ParseSectionHeader.h>
#include <data/ParseTransferFunctionControlPoint.h>
#include <data/KeyValuePair.h>
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

    bool DoesLineContainSectionHeader(const std::string& line)
    {
        return line[0] == '[';
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
    unsigned int currentElementIndex = 0;

    while (std::getline(file, line))
    {
        TrimWhitespaceInLine(line);

        if (!DoesLineContainData(line))
        {
            continue;
        }

        if (DoesLineContainSectionHeader(line))
        {
            currentSection = Parsing::ParseSectionHeader(line);
            continue;
        }

        if (currentSection == ApplicationStateIniFileSection::TransferFunctionPoint
         || currentSection == ApplicationStateIniFileSection::PointLight)
        {
            auto elementIndexParseResult = Parsing::ParseElementIndex(line, currentSection);

            if (elementIndexParseResult)
            {
                currentElementIndex = elementIndexParseResult.value();
            }
            else
            {
                return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
            }
            continue;
        }

        KeyValuePair keyValuePair = Parsing::ParseKeyValuePair(line);
        const std::string& keyString = keyValuePair.key;
        const std::string& valueString = keyValuePair.value;
        ApplicationStateIniFileKey key = GetApplicationStateIniFileKey(keyString);

        switch (currentSection)
        {
            case ApplicationStateIniFileSection::Camera:
            {
                const bool cameraParameterParseSuccess = Parsing::ParseCameraParameter(key, valueString, cameraParameters);
                
                if (!cameraParameterParseSuccess)
                {
                    return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
                }
                break;
            }

            case ApplicationStateIniFileSection::TransferFunctionPoint:
            {
                TransferFunctionControlPoint& point = guiParameters.transferFunction.controlPoints[currentElementIndex];

                const bool transferFunctionPointParseSuccess = Parsing::ParseTransferFunctionControlPoint(key, valueString, point);

                if (!transferFunctionPointParseSuccess)
                {
                    return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
                }
                break;
            }

            case ApplicationStateIniFileSection::SSAO:
            case ApplicationStateIniFileSection::DirectionalLight:
            case ApplicationStateIniFileSection::PointLight:
            case ApplicationStateIniFileSection::Rendering:
            {
                const bool guiParameterParseSuccess = Parsing::ParseGuiParameter(
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

    return ApplicationState
    {
        .cameraParameters = cameraParameters,
        .guiParameters = guiParameters
    };
}
