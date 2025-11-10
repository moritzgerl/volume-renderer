#include <data/MakeDefaultApplicationState.h>
#include <camera/MakeDefaultCameraParameters.h>
#include <gui/MakeDefaultGuiParameters.h>

Data::ApplicationState Factory::MakeDefaultApplicationState()
{
    Data::ApplicationState applicationState
    {
        .cameraParameters = MakeDefaultCameraParameters(),
        .guiParameters = MakeDefaultGuiParameters()
    };

    return applicationState;
}