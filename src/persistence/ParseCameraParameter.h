/**
* \file ParseCameraParameter.h
*
* \brief Function for parsing camera parameters from INI file values.
*/

#ifndef PARSE_CAMERA_PARAMETER_H
#define PARSE_CAMERA_PARAMETER_H

#include <persistence/ApplicationStateIniFileLoadingError.h>
#include <persistence/ApplicationStateIniFileKey.h>
#include <camera/CameraParameters.h>

#include <expected>
#include <string_view>

namespace Persistence
{
    /**
    * Parses and applies a camera parameter from an INI file value.
    *
    * Converts the string value to the appropriate type based on the parameter
    * key and updates the corresponding field in the CameraParameters structure.
    * Supported parameters include camera position (PositionX, PositionY, PositionZ)
    * and zoom level. Returns an error if the value cannot be parsed or is invalid.
    *
    * @param key The parameter key identifying which camera field to update.
    * @param valueString The string value to parse.
    * @param cameraParameters The camera parameters structure to update.
    * @return Expected containing either void on success or an error code on failure.
    *
    * @see CameraParameters for camera state structure.
    * @see ApplicationStateIniFileKey for parameter key identifiers.
    * @see ApplicationStateIniFileLoadingError for error codes.
    */
    std::expected<void, ApplicationStateIniFileLoadingError> ParseCameraParameter(
       ApplicationStateIniFileKey key,
       std::string_view valueString,
       CameraParameters& cameraParameters);
}

#endif
