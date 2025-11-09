#include <data/MakeDefaultSaveState.h>
#include <config/Config.h>

Data::SaveState Data::MakeDefaultSaveState()
{
    SaveState saveState{};
    saveState.transferFunction = Config::defaultTransferFunction;
    return saveState;
}
