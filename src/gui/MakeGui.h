#ifndef MAKE_GUI_H
#define MAKE_GUI_H

#include <gui/Gui.h>

class Storage;

namespace Factory
{
    Gui MakeGui(Storage& storage);
}

#endif
