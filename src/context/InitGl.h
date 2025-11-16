/**
* \file InitGl.h
*
* \brief Function for initializing OpenGL state.
*/

#ifndef INIT_GL_H
#define INIT_GL_H

namespace Context
{
    /**
    * Initializes OpenGL state and settings.
    *
    * Configures OpenGL state including depth testing, blending, and
    * other rendering settings. This function should be called once
    * after creating the OpenGL context and loading GLAD.
    *
    * @return void
    *
    * @see InitGlad for loading OpenGL function pointers.
    * @see InitGlfw for GLFW library initialization.
    * @see GlfwWindow for window and context creation.
    */
    void InitGl();
}

#endif
