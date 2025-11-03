#include <storage/FrameBufferStorage.h>
#include <algorithm>
#include <iostream>

FrameBufferStorage::FrameBufferStorage(std::vector<FrameBuffer>&& frameBuffers)
    : m_frameBuffers(std::move(frameBuffers))
{
}

const FrameBuffer& FrameBufferStorage::GetFrameBuffer(FrameBufferId frameBufferId) const
{
    auto frameBufferIter = std::find_if(m_frameBuffers.cbegin(), m_frameBuffers.cend(),
        [frameBufferId]
        (const FrameBuffer& frameBuffer)
    {
        return frameBuffer.GetFrameBufferId() == frameBufferId;
    }
    );

    if (frameBufferIter == m_frameBuffers.end())
    {
        std::cerr << "FrameBufferStorage::GetFrameBuffer - could not find framebuffer with the specified FrameBufferId" << std::endl;
        return m_frameBuffers[0];
    }

    return *frameBufferIter;
}
