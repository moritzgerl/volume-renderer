/**
* \file CameraParameters.h
*
* \brief Serializable camera state structure.
*/

#ifndef CAMERA_PARAMETERS_H
#define CAMERA_PARAMETERS_H

#include <glm/glm.hpp>

/**
* \struct CameraParameters
*
* \brief Holds serializable camera state for persistence.
*
* Contains the essential camera parameters that can be saved to and loaded from an INI file.
* Used for application state persistence across sessions.
*
* @see Camera for the camera implementation that uses these parameters.
* @see LoadApplicationStateFromIniFile for loading camera parameters from disk.
* @see SaveApplicationStateToIniFile for saving camera parameters to disk.
*/
struct CameraParameters
{
    glm::vec3 position; /**< Camera position in world space. */
    glm::vec3 lookAt; /**< Point in world space the camera looks at. */
    glm::vec3 up; /**< World-space up vector for orientation. */
    float zoom; /**< Field of view angle in degrees. */
};

#endif
