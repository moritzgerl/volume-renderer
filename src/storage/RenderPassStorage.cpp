#include <storage/RenderPassStorage.h>

RenderPassStorage::RenderPassStorage(std::vector<RenderPass>&& renderPasses)
    : m_storage(std::move(renderPasses))
{
}

const RenderPass& RenderPassStorage::GetRenderPass(RenderPassId renderPassId) const
{
    return m_storage.GetElement(renderPassId);
}

const std::vector<RenderPass>& RenderPassStorage::GetRenderPasses() const
{
    return m_storage.GetElements();
}
