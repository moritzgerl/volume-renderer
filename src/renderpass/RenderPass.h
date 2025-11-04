#ifndef RENDER_PASS_H
#define RENDER_PASS_H

#include <renderpass/RenderPassId.h>
#include <functional>
#include <vector>

class ScreenQuad;
class Shader;
class FrameBuffer;
class Texture;

class RenderPass
{
public:
    RenderPass(
        RenderPassId renderPassId,
        const ScreenQuad& screenQuad,
        const Shader& shader,
        const FrameBuffer& frameBuffer,
        std::vector<std::reference_wrapper<const Texture>>&& textures,
        std::function<void()>&& prepareFunction,
        std::function<void()>&& renderFunction
    );

    RenderPassId GetId() const;
    void Render() const;

private:
    RenderPassId m_renderPassId;
    const ScreenQuad& m_screenQuad;
    const Shader& m_shader;
    const FrameBuffer& m_frameBuffer;
    std::vector<std::reference_wrapper<const Texture>> m_textures;
    std::function<void()> m_prepareFunction;
    std::function<void()> m_renderFunction;
};

#endif
