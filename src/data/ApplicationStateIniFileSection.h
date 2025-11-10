#ifndef APPLICATION_STATE_INI_FILE_SECTION_H
#define APPLICATION_STATE_INI_FILE_SECTION_H

namespace Data
{
    enum class ApplicationStateIniFileSection
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
