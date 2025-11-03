#include <storage/RenderPassStorage.h>
#include <algorithm>
#include <iostream>

RenderPassStorage::RenderPassStorage(std::vector<RenderPass>&& renderPasses)
    : m_renderPasses(std::move(renderPasses))
{
}

const RenderPass& RenderPassStorage::GetRenderPass(RenderPassId renderPassId) const
{
    auto renderPassIter = std::find_if(m_renderPasses.cbegin(), m_renderPasses.cend(),
        [renderPassId]
        (const RenderPass& renderPass)
        {
            return renderPass.GetRenderPassId() == renderPassId;
        }
    );

    if (renderPassIter == m_renderPasses.end())
    {
        std::cerr << "RenderPassStorage::GetRenderPass - could not find render pass with the specified RenderPassId" << std::endl;
        return m_renderPasses[0];
    }

    return *renderPassIter;
}

const std::vector<RenderPass>& RenderPassStorage::GetRenderPasses() const
{
    return m_renderPasses;
}
