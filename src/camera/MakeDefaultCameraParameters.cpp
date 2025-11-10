#include <camera/MakeDefaultCameraParameters.h>
#include <config/Config.h>

CameraParameters MakeDefaultCameraParameters()
{
    // TODO use ctor
    CameraParameters cameraParameters;
    cameraParameters.position = Config::defaultCameraPosition;
    cameraParameters.lookAt = Config::defaultCameraLookAt;
    cameraParameters.up = Config::defaultCameraUp;
    cameraParameters.zoom = Config::defaultCameraZoom;
    return cameraParameters;
}
