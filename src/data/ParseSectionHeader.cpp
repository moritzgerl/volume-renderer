#include <data/ParseSectionHeader.h>

Data::ApplicationStateIniFileSection Parsing::ParseSectionHeader(std::string_view line)
{
    // TODO use constexpr lookup
    if (line == "[Camera]")
    {
        return Data::ApplicationStateIniFileSection::Camera;
    }
    else if (line == "[GuiParameters]")
    {
        return Data::ApplicationStateIniFileSection::GuiParameters;
    }
    else if (line == "[TransferFunction]")
    {
        return Data::ApplicationStateIniFileSection::TransferFunction;
    }
    else if (line == "[SSAO]")
    {
        return Data::ApplicationStateIniFileSection::SSAO;
    }
    else if (line == "[DirectionalLight]")
    {
        return Data::ApplicationStateIniFileSection::DirectionalLight;
    }
    else if (line == "[Rendering]")
    {
        return Data::ApplicationStateIniFileSection::Rendering;
    }
    else if (line.substr(0, 22) == "[TransferFunctionPoint")
    {
        return Data::ApplicationStateIniFileSection::TransferFunctionPoint;
    }
    else if (line.substr(0, 11) == "[PointLight")
    {
        return Data::ApplicationStateIniFileSection::PointLight;
    }    
}
