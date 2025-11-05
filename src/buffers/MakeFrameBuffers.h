#ifndef MAKE_FRAME_BUFFERS_H
#define MAKE_FRAME_BUFFERS_H

#include <buffers/FrameBuffer.h>
#include <storage/StorageTypes.h>
#include <vector>

namespace Factory
{
    std::vector<FrameBuffer> MakeFrameBuffers(const TextureStorage& textureStorage);
}

#endif
