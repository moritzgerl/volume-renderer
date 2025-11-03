#include <renderpass/RenderPass.h>
#include <buffers/FrameBuffer.h>
#include <shader/Shader.h>
#include <textures/Texture.h>

RenderPass::RenderPass(
    RenderPassId renderPassId,
    const ScreenQuad& screenQuad,
    const Shader& shader,
    const FrameBuffer& frameBuffer,
    std::vector<std::reference_wrapper<const Texture>>&& textures,
    std::function<void()>&& prepareFunction,
    std::function<void()>&& renderFunction)
    : m_renderPassId(renderPassId)
    , m_screenQuad(screenQuad)
    , m_shader(shader)
    , m_frameBuffer(frameBuffer)
    , m_textures(std::move(textures))
    , m_prepareFunction(std::move(prepareFunction))
    , m_renderFunction(std::move(renderFunction))
{
}

RenderPassId RenderPass::GetRenderPassId() const
{
    return m_renderPassId;
}

void RenderPass::Render() const
{
    m_frameBuffer.Bind();
    m_shader.Use();

    m_prepareFunction();

    for (const auto& texture : m_textures)
    {
        texture.get().Bind();
    }

    m_renderFunction();

    m_frameBuffer.Unbind();
}
