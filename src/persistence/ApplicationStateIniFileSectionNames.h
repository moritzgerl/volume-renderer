/**
* \file ApplicationStateIniFileSectionNames.h
*
* \brief Constant string literals for INI file section headers.
*/

#ifndef APPLICATION_STATE_INI_FILE_SECTION_NAMES_H
#define APPLICATION_STATE_INI_FILE_SECTION_NAMES_H

#include <string_view>

/**
* \namespace Persistence::SectionNames
*
* \brief Contains constant string literals for INI file section headers.
*
* Provides compile-time constant string views for all section header names
* used in application state INI files. These constants are used for both
* parsing (comparing against input) and serialization (writing headers).
*
* Regular sections use complete header strings (e.g., "[Camera]"), while
* indexed sections use prefixes (e.g., "[TransferFunctionPoint") that are
* concatenated with indices during serialization.
*
* @see ApplicationStateIniFileSection for section identifier enumeration.
* @see GetApplicationStateIniFileSection for mapping strings to enum values.
* @see SaveApplicationStateToIniFile for writing section headers.
*/
namespace Persistence::SectionNames
{
    constexpr std::string_view camera = "[Camera]";                          /**< Camera parameters section. */
    constexpr std::string_view guiParameters = "[GuiParameters]";            /**< GUI parameters section (deprecated). */
    constexpr std::string_view transferFunction = "[TransferFunction]";      /**< Transfer function configuration section. */
    constexpr std::string_view trackball = "[Trackball]";                    /**< Trackball control settings section. */
    constexpr std::string_view ssao = "[SSAO]";                              /**< SSAO configuration section. */
    constexpr std::string_view directionalLight = "[DirectionalLight]";      /**< Directional light properties section. */
    constexpr std::string_view rendering = "[Rendering]";                    /**< Rendering settings section. */
    constexpr std::string_view transferFunctionPointPrefix = "[TransferFunctionPoint";  /**< Prefix for indexed transfer function points (e.g., "[TransferFunctionPoint:0]"). */
    constexpr std::string_view pointLightPrefix = "[PointLight";             /**< Prefix for indexed point lights (e.g., "[PointLight:0]"). */
}

#endif
