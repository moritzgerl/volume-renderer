/**
* \file MakeInputHandler.h
*
* \brief Factory function for creating the input handler.
*/

#ifndef MAKE_INPUT_HANDLER_H
#define MAKE_INPUT_HANDLER_H

#include <input/InputHandler.h>

class Storage;

namespace Factory
{
    /**
    * Creates and initializes the input handler for keyboard and mouse input.
    *
    * Constructs an InputHandler that processes user input from keyboard and mouse
    * to control camera movement, GUI visibility, and debug display modes. The
    * input handler registers GLFW callbacks for the window and updates camera
    * and display properties in response to user interaction.
    *
    * @param storage Storage containing camera, display properties, and GLFW window.
    * @return Initialized InputHandler object.
    *
    * @see InputHandler for input processing implementation.
    * @see Camera for camera state management.
    * @see DisplayProperties for display mode configuration.
    */
    InputHandler MakeInputHandler(Storage& storage);
}

#endif
