/**
* \file MakeGui.h
*
* \brief Factory function for creating the graphical user interface.
*/

#ifndef MAKE_GUI_H
#define MAKE_GUI_H

#include <gui/Gui.h>

class Storage;

namespace Factory
{
    /**
    * Creates and initializes the ImGui-based graphical user interface.
    *
    * Constructs a Gui object that provides runtime controls for adjusting
    * rendering parameters including lighting (directional and point lights),
    * SSAO settings (kernel size, radius, bias), and transfer function control
    * points. The GUI modifies GuiParameters and sets GuiUpdateFlags to trigger
    * resource regeneration when needed.
    *
    * @param storage Storage containing GUI parameters, update flags, transfer function, and window.
    * @return Initialized Gui object.
    *
    * @see Gui for GUI rendering implementation.
    * @see GuiParameters for runtime rendering parameters.
    * @see GuiUpdateFlags for resource update tracking.
    * @see TransferFunctionGui for transfer function editing.
    */
    Gui MakeGui(Storage& storage);
}

#endif
