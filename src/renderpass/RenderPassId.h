#ifndef RENDER_PASS_ID_H
#define RENDER_PASS_ID_H

enum class RenderPassId
{
    Setup,
    SsaoInput,
    Ssao,
    SsaoBlur,
    SsaoFinal,
    LightSource,
    Debug,
    Unknown
};

#endif
