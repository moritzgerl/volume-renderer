#ifndef MAKE_FRAME_BUFFERS_H
#define MAKE_FRAME_BUFFERS_H

#include <buffers/FrameBuffer.h>
#include <vector>

class TextureStorage;

namespace Factory
{
    std::vector<FrameBuffer> MakeFrameBuffers(const TextureStorage& textureStorage);
}

#endif
