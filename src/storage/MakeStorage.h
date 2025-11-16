/**
* \file MakeStorage.h
*
* \brief Factory function for creating and initializing the central storage system.
*/

#ifndef MAKE_STORAGE_H
#define MAKE_STORAGE_H

#include <storage/Storage.h>

namespace Factory
{
    /**
    * Creates and initializes the central storage system with all application resources.
    *
    * Constructs the Storage object containing all application state and OpenGL resources
    * including camera, display properties, GUI parameters, primitives (screen quad, unit
    * cube), SSAO kernel, textures, shaders, framebuffers, volume data, transfer function,
    * and GLFW window. All components are initialized in the correct dependency order.
    * This is the primary entry point for application initialization.
    *
    * @return Fully initialized Storage object containing all application resources.
    *
    * @see Storage for centralized resource management.
    * @see MakeTextures for texture creation.
    * @see MakeShaders for shader creation.
    * @see MakeFrameBuffers for framebuffer creation.
    */
    Storage MakeStorage();
}

#endif
