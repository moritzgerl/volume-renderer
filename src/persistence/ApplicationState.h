/**
* \file ApplicationState.h
*
* \brief Application state structure for persistence to INI files.
*/

#ifndef APPLICATION_STATE_H
#define APPLICATION_STATE_H

#include <camera/CameraParameters.h>
#include <gui/GuiParameters.h>

namespace Persistence
{
    /**
    * \struct ApplicationState
    *
    * \brief Serializable application state for saving/loading configuration.
    *
    * Aggregates all application parameters that should be persisted between
    * sessions, including camera position/orientation and GUI parameter values.
    * This structure is serialized to and deserialized from INI files to preserve
    * user settings across application restarts.
    *
    * @see LoadApplicationStateFromIniFile for deserializing from INI files.
    * @see SaveApplicationStateToIniFile for serializing to INI files.
    * @see CameraParameters for camera configuration.
    * @see GuiParameters for GUI settings including lighting and transfer function.
    */
    struct ApplicationState
    {
        CameraParameters cameraParameters; /**< Camera position, target, and up vector. */
        GuiParameters guiParameters; /**< GUI parameters including lighting, SSAO, and transfer function settings. */
    };
}

#endif
