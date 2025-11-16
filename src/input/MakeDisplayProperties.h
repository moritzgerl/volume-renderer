/**
* \file MakeDisplayProperties.h
*
* \brief Factory function for creating display properties.
*/

#ifndef MAKE_DISPLAY_PROPERTIES_H
#define MAKE_DISPLAY_PROPERTIES_H

#include <input/DisplayProperties.h>

namespace Factory
{
    /**
    * Creates and initializes display properties with default values.
    *
    * Constructs a DisplayProperties object with default settings for GUI
    * visibility and debug display modes. Display properties control which
    * elements are rendered and which debug visualizations are shown.
    *
    * @return Initialized DisplayProperties object with default values.
    *
    * @see DisplayProperties for display mode configuration.
    * @see InputHandler for runtime display property updates.
    */
    DisplayProperties MakeDisplayProperties();
}

#endif
