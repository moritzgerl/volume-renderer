#ifndef PARSE_CAMERA_PARAMETER_H
#define PARSE_CAMERA_PARAMETER_H

#include <persistence/ApplicationStateIniFileLoadingError.h>
#include <persistence/ApplicationStateIniFileKey.h>
#include <camera/CameraParameters.h>
#include <string_view>

namespace Persistence
{   
    // TODO find a better return type
    bool ParseCameraParameter(
       ApplicationStateIniFileKey key,
       std::string_view valueString, 
       CameraParameters& cameraParameters);
}

#endif
