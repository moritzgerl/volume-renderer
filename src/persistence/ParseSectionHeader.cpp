#include <persistence/ParseSectionHeader.h>
#include <persistence/GetApplicationStateIniFileSection.h>

namespace
{
    constexpr std::string_view transferFunctionPointPrefix = "[TransferFunctionPoint";
    constexpr std::string_view pointLightPrefix = "[PointLight";
}

Persistence::ApplicationStateIniFileSection Persistence::ParseSectionHeader(std::string_view line)
{
    if (line.starts_with(transferFunctionPointPrefix))
    {
        return ApplicationStateIniFileSection::TransferFunctionPoint;
    }

    else if (line.starts_with(pointLightPrefix))
    {
        return ApplicationStateIniFileSection::PointLight;
    }

    else
    {
        return GetApplicationStateIniFileSection(line);
    }
}
