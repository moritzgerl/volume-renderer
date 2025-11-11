#include <persistence/ParseSectionHeader.h>

Persistence::ApplicationStateIniFileSection Persistence::ParseSectionHeader(std::string_view line)
{
    // TODO use constexpr lookup
    if (line == "[Camera]")
    {
        return ApplicationStateIniFileSection::Camera;
    }
    else if (line == "[GuiParameters]")
    {
        return ApplicationStateIniFileSection::GuiParameters;
    }
    else if (line == "[TransferFunction]")
    {
        return ApplicationStateIniFileSection::TransferFunction;
    }
    else if (line == "[SSAO]")
    {
        return ApplicationStateIniFileSection::SSAO;
    }
    else if (line == "[DirectionalLight]")
    {
        return ApplicationStateIniFileSection::DirectionalLight;
    }
    else if (line == "[Rendering]")
    {
        return ApplicationStateIniFileSection::Rendering;
    }
    else if (line.substr(0, 22) == "[TransferFunctionPoint")
    {
        return ApplicationStateIniFileSection::TransferFunctionPoint;
    }
    else if (line.substr(0, 11) == "[PointLight")
    {
        return ApplicationStateIniFileSection::PointLight;
    }

    return ApplicationStateIniFileSection::None;
}
