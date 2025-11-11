#ifndef APPLICATION_STATE_INI_FILE_SECTION_NAMES_H
#define APPLICATION_STATE_INI_FILE_SECTION_NAMES_H

#include <string_view>

namespace Persistence::SectionNames
{
    constexpr std::string_view camera = "[Camera]";
    constexpr std::string_view guiParameters = "[GuiParameters]";
    constexpr std::string_view transferFunction = "[TransferFunction]";
    constexpr std::string_view trackball = "[Trackball]";
    constexpr std::string_view ssao = "[SSAO]";
    constexpr std::string_view directionalLight = "[DirectionalLight]";
    constexpr std::string_view rendering = "[Rendering]";
    constexpr std::string_view transferFunctionPointPrefix = "[TransferFunctionPoint";
    constexpr std::string_view pointLightPrefix = "[PointLight";
}

#endif
