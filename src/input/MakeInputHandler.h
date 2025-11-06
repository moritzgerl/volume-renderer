#ifndef MAKE_INPUT_HANDLER_H
#define MAKE_INPUT_HANDLER_H

#include <input/InputHandler.h>

class Storage;

namespace Factory
{
    InputHandler MakeInputHandler(Storage& storage);
}

#endif
