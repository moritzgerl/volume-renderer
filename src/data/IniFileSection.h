#ifndef INI_FILE_SECTION_H
#define INI_FILE_SECTION_H

namespace Data
{
    enum class IniFileSection
    {
        None,
        GuiParameters,
        TransferFunction,
        TransferFunctionPoint,
        Camera,
        SSAO,
        DirectionalLight,
        PointLight,
        Rendering
    };
}

#endif
