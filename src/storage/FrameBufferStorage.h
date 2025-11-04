#ifndef FRAME_BUFFER_STORAGE_H
#define FRAME_BUFFER_STORAGE_H

#include <buffers/FrameBuffer.h>
#include <buffers/FrameBufferId.h>
#include <storage/ElementStorage.h>

class FrameBufferStorage
{
public:
    FrameBufferStorage(std::vector<FrameBuffer>&& frameBuffers);
    const FrameBuffer& GetFrameBuffer(FrameBufferId frameBufferId) const;

private:
    ElementStorage<FrameBuffer, FrameBufferId> m_storage;
};

#endif
