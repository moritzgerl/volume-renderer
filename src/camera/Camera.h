// Copyright https://learnopengl.com/

/**
* \file Camera.h
*
* \brief Camera system for 3D navigation and view transformation.
*/

#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

struct CameraParameters;

/**
* \class Camera
*
* \brief Camera for 3D navigation using trackball-style mouse controls.
*
* Manages camera position, orientation, and view transformation for the 3D scene.
* Supports mouse-based rotation (trackball controls) and zoom via mouse scroll.
* The camera always looks at a specified point in 3D space while rotating around it.
*
* Camera state can be serialized to/from CameraParameters for persistence.
* Default camera parameters are defined in Config namespace.
*
* Based on camera implementation from https://learnopengl.com/
*
* @see CameraParameters for serializable camera state.
* @see InputHandler for processing mouse input and updating the camera.
* @see Config for default camera configuration values.
*/
class Camera
{
public:
    /**
    * Constructor.
    * @param cameraParameters The initial camera parameters (position, look-at point, up vector, zoom).
    */
    Camera(const CameraParameters& cameraParameters);

    float GetZoom() const;
    glm::vec3 GetPosition() const;

    /**
    * Computes the view matrix for rendering.
    * @return glm::mat4 The view transformation matrix.
    */
    glm::mat4 GetViewMatrix() const;

    /**
    * Retrieves current camera parameters for serialization.
    * @return CameraParameters The current camera state.
    */
    CameraParameters GetCameraParameters() const;

    /**
    * Processes mouse scroll input for zooming.
    * @param yoffset The vertical scroll offset.
    * @return void
    */
    void ProcessMouseScroll(float yoffset);

    /**
    * Processes mouse movement for trackball rotation.
    * @param xoffset The horizontal mouse movement.
    * @param yoffset The vertical mouse movement.
    * @param invertY Whether to invert the Y-axis rotation.
    * @param sensitivity The rotation sensitivity multiplier.
    * @return void
    */
    void ProcessMouseMovement(float xoffset, float yoffset, bool invertY, float sensitivity);

private:
    float m_zoom; /**< Field of view angle in degrees. */
    glm::vec3 m_position; /**< Camera position in world space. */
    glm::vec3 m_lookAt; /**< Point in world space the camera looks at. */
    glm::vec3 m_worldUp; /**< World-space up vector for orientation. */
    glm::vec3 m_front; /**< Camera front direction vector (normalized). */
    glm::vec3 m_right; /**< Camera right direction vector (normalized). */
    glm::vec3 m_up; /**< Camera up direction vector (normalized). */
};

#endif
