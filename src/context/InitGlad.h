/**
* \file InitGlad.h
*
* \brief Function for initializing GLAD OpenGL function loader.
*/

#ifndef INIT_GLAD_H
#define INIT_GLAD_H

namespace Context
{
    /**
    * Initializes the GLAD OpenGL function loader.
    *
    * Loads all OpenGL function pointers using GLAD. This function must be
    * called after creating an OpenGL context and before making any OpenGL
    * calls. It uses GLFW's getProcAddress to load function pointers for
    * the current OpenGL context.
    *
    * @return void
    *
    * @see InitGlfw for GLFW library initialization.
    * @see InitGl for OpenGL state initialization.
    * @see GlfwWindow for window and context creation.
    */
    void InitGlad();
}

#endif
