#include <camera/MakeDefaultCameraParameters.h>
#include <config/Config.h>

CameraParameters Factory::MakeDefaultCameraParameters()
{
    return CameraParameters	{
        Config::defaultCameraPosition,
        Config::defaultCameraLookAt,
        Config::defaultCameraUp,
        Config::defaultCameraZoom
    };
}
