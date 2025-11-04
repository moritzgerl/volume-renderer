#ifndef RENDER_PASS_STORAGE_H
#define RENDER_PASS_STORAGE_H

#include <renderpass/RenderPass.h>
#include <renderpass/RenderPassId.h>
#include <storage/ElementStorage.h>

class RenderPassStorage
{
public:
    RenderPassStorage(std::vector<RenderPass>&& renderPasses);
    const RenderPass& GetRenderPass(RenderPassId renderPassId) const;
    const std::vector<RenderPass>& GetRenderPasses() const;

private:
    ElementStorage<RenderPass, RenderPassId> m_storage;
};

#endif
