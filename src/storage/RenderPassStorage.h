#ifndef RENDER_PASS_STORAGE_H
#define RENDER_PASS_STORAGE_H

#include <renderpass/RenderPass.h>
#include <renderpass/RenderPassId.h>
#include <vector>

class RenderPassStorage
{
public:
    RenderPassStorage(std::vector<RenderPass>&& renderPasses);
    const RenderPass& GetRenderPass(RenderPassId renderPassId) const;

private:
    std::vector<RenderPass> m_renderPasses;
};

#endif
