#include <persistence/ParseSectionHeader.h>
#include <persistence/ApplicationStateIniFileSectionNames.h>
#include <persistence/GetApplicationStateIniFileSection.h>

Persistence::ApplicationStateIniFileSection Persistence::ParseSectionHeader(std::string_view line)
{
    if (line.starts_with(SectionNames::transferFunctionPointPrefix))
    {
        return ApplicationStateIniFileSection::TransferFunctionPoint;
    }

    else if (line.starts_with(SectionNames::pointLightPrefix))
    {
        return ApplicationStateIniFileSection::PointLight;
    }

    else
    {
        return GetApplicationStateIniFileSection(line);
    }
}
