#ifndef PARSE_CAMERA_PARAMETER_H
#define PARSE_CAMERA_PARAMETER_H

#include <data/ApplicationStateIniFileLoadingError.h>
#include <data/ApplicationStateIniFileKey.h>
#include <camera/CameraParameters.h>
#include <string_view>

namespace Parsing
{   
    // TODO find a better return type
    bool ParseCameraParameter(
       Data::ApplicationStateIniFileKey key,
       std::string_view valueString, 
       CameraParameters& cameraParameters);
}

#endif
