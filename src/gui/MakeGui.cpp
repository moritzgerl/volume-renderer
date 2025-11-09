#include <gui/MakeGui.h>
#include <storage/Storage.h>

namespace Factory
{
    Gui MakeGui(Storage& storage)
    {
        return Gui(
            storage.GetWindow().GetWindow(),
            storage.GetSaveState(),
            storage.GetGuiParameters(),
            storage.GetGuiUpdateFlags());
    }
}
