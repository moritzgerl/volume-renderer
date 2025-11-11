#ifndef APPLICATION_STATE_H
#define APPLICATION_STATE_H

#include <camera/CameraParameters.h>
#include <gui/GuiParameters.h>

namespace Persistence
{
    struct ApplicationState
    {
        CameraParameters cameraParameters;
        GuiParameters guiParameters;
    };
}

#endif
