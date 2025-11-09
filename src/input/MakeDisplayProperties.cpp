#include <config/Config.h>
#include <input/MakeDisplayProperties.h>

DisplayProperties Factory::MakeDisplayProperties()
{
    DisplayProperties displayProperties;
    displayProperties.showSsaoMap = false;
    return displayProperties;
}
