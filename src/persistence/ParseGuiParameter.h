/**
* \file ParseGuiParameter.h
*
* \brief Function for parsing GUI parameters from INI file values.
*/

#ifndef PARSE_GUI_PARAMETER_H
#define PARSE_GUI_PARAMETER_H

#include <persistence/ApplicationStateIniFileLoadingError.h>
#include <persistence/ApplicationStateIniFileSection.h>
#include <persistence/ApplicationStateIniFileKey.h>
#include <gui/GuiParameters.h>

#include <expected>
#include <string_view>

namespace Persistence
{
    /**
    * Parses and applies a GUI parameter from an INI file value.
    *
    * Converts the string value to the appropriate type based on the section,
    * parameter key, and element index, then updates the corresponding field in
    * the GuiParameters structure. Handles various parameter types including
    * trackball settings, SSAO configuration, directional light properties,
    * point light properties (indexed), and general rendering settings. Returns
    * an error if the value cannot be parsed or is invalid.
    *
    * @param section The INI file section containing the parameter.
    * @param key The parameter key identifying which GUI field to update.
    * @param elementIndex The index for array elements (e.g., point light number).
    * @param valueString The string value to parse.
    * @param guiParameters The GUI parameters structure to update.
    * @return Expected containing either void on success or an error code on failure.
    *
    * @see GuiParameters for GUI parameters structure.
    * @see ApplicationStateIniFileSection for section identifiers.
    * @see ApplicationStateIniFileKey for parameter key identifiers.
    * @see ApplicationStateIniFileLoadingError for error codes.
    */
    std::expected<void, ApplicationStateIniFileLoadingError> ParseGuiParameter(
        ApplicationStateIniFileSection section,
        ApplicationStateIniFileKey key,
        unsigned int elementIndex,
        std::string_view valueString,
        GuiParameters& guiParameters);
}

#endif
