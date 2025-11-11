#include <persistence/MakeDefaultApplicationState.h>
#include <camera/MakeDefaultCameraParameters.h>
#include <gui/MakeDefaultGuiParameters.h>

Persistence::ApplicationState Factory::MakeDefaultApplicationState()
{
    Persistence::ApplicationState applicationState
    {
        .cameraParameters = MakeDefaultCameraParameters(),
        .guiParameters = MakeDefaultGuiParameters()
    };

    return applicationState;
}
