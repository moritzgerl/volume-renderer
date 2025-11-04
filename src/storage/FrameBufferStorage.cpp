#include <storage/FrameBufferStorage.h>

FrameBufferStorage::FrameBufferStorage(std::vector<FrameBuffer>&& frameBuffers)
    : m_storage(std::move(frameBuffers))
{
}

const FrameBuffer& FrameBufferStorage::GetFrameBuffer(FrameBufferId frameBufferId) const
{
    return m_storage.GetElement(frameBufferId);
}
