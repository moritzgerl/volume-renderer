/**
* \file MakeDefaultApplicationState.h
*
* \brief Factory function for creating application state with default values.
*/

#ifndef MAKE_DEFAULT_APPLICATION_STATE_H
#define MAKE_DEFAULT_APPLICATION_STATE_H

#include <persistence/ApplicationState.h>

namespace Factory
{
    /**
    * Creates application state with default values for all components.
    *
    * Constructs an ApplicationState object initialized with default values for
    * camera parameters, GUI parameters, and transfer function control points.
    * This provides a consistent starting state for the application when no
    * persisted state file is available.
    *
    * @return ApplicationState object with default values.
    *
    * @see ApplicationState for state serialization structure.
    * @see MakeDefaultCameraParameters for default camera settings.
    * @see MakeDefaultGuiParameters for default GUI settings.
    * @see LoadApplicationStateFromIniFile for loading persisted state.
    */
    Persistence::ApplicationState MakeDefaultApplicationState();
}

#endif
