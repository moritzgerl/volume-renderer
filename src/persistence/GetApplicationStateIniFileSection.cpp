#include <persistence/GetApplicationStateIniFileSection.h>
#include <persistence/ApplicationStateIniFileSectionNames.h>

#include <algorithm>
#include <array>

namespace
{
    using Section = Persistence::ApplicationStateIniFileSection;
    namespace SectionNames = Persistence::SectionNames;

    struct ApplicationStateIniFileSectionMapping
    {
        std::string_view stringSection;
        Section enumSection;
    };

    constexpr std::array<ApplicationStateIniFileSectionMapping, 7> applicationStateIniFileSectionLookup =
    {{
        {SectionNames::camera, Section::Camera},
        {SectionNames::guiParameters, Section::GuiParameters},
        {SectionNames::transferFunction, Section::TransferFunction},
        {SectionNames::trackball, Section::Trackball},
        {SectionNames::ssao, Section::SSAO},
        {SectionNames::directionalLight, Section::DirectionalLight},
        {SectionNames::rendering, Section::Rendering}
    }};
}

Persistence::ApplicationStateIniFileSection Persistence::GetApplicationStateIniFileSection(std::string_view line)
{
    auto it = std::find_if(applicationStateIniFileSectionLookup.begin(), applicationStateIniFileSectionLookup.end(),
        [line](const ApplicationStateIniFileSectionMapping& mapping)
        {
            return mapping.stringSection == line;
        });

    if (it != applicationStateIniFileSectionLookup.end())
    {
        return it->enumSection;
    }
    else
    {
        return ApplicationStateIniFileSection::None;
    }
}
