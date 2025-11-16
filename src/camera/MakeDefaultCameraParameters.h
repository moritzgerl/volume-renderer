/**
* \file MakeDefaultCameraParameters.h
*
* \brief Factory function for creating camera parameters with default values.
*/

#ifndef MAKE_DEFAULT_CAMERA_PARAMETERS_H
#define MAKE_DEFAULT_CAMERA_PARAMETERS_H

#include <camera/CameraParameters.h>

namespace Factory
{
    /**
    * Creates camera parameters with default view settings.
    *
    * Constructs a CameraParameters object initialized with default values
    * for camera position, target, up vector, field of view, and near/far
    * clipping planes. The default configuration provides a standard view
    * of the volume suitable for initial exploration.
    *
    * @return CameraParameters object with default view settings.
    *
    * @see CameraParameters for camera state serialization.
    * @see Camera for camera implementation.
    */
    CameraParameters MakeDefaultCameraParameters();
}

#endif
