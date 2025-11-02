#include <config/Config.h>
#include <input/MakeDisplayProperties.h>

DisplayProperties Factory::MakeDisplayProperties()
{
    DisplayProperties displayProperties;
    displayProperties.showGui = Config::showGuiByDefault;
    return displayProperties;
}
