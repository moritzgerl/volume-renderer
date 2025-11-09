#include <gui/GuiParameters.h>
#include <data/SaveState.h>

#include <optional>

namespace Factory
{
    GuiParameters MakeGuiParameters(const std::optional<Data::SaveState>& saveState = std::nullopt);
}