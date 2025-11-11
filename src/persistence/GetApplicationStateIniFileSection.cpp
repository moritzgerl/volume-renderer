#include <persistence/GetApplicationStateIniFileSection.h>

#include <algorithm>
#include <array>

namespace
{
    using Section = Persistence::ApplicationStateIniFileSection;

    struct ApplicationStateIniFileSectionMapping
    {
        std::string_view stringSection;
        Section enumSection;
    };

    constexpr std::array<ApplicationStateIniFileSectionMapping, 7> applicationStateIniFileSectionLookup =
    {{
        {"[Camera]", Section::Camera},
        {"[GuiParameters]", Section::GuiParameters},
        {"[TransferFunction]", Section::TransferFunction},
        {"[Trackball]", Section::Trackball},
        {"[SSAO]", Section::SSAO},
        {"[DirectionalLight]", Section::DirectionalLight},
        {"[Rendering]", Section::Rendering}
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
