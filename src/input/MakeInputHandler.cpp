#include <input/MakeInputHandler.h>
#include <storage/Storage.h>

InputHandler Factory::MakeInputHandler(Storage& storage)
{ 
    return InputHandler(
        storage.GetWindow().GetWindow(),
        storage.GetCamera(),
        storage.GetDisplayProperties());
}
