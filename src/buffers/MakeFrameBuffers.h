#ifndef MAKE_FRAME_BUFFERS_H
#define MAKE_FRAME_BUFFERS_H

#include <buffers/FrameBuffer.h>
#include <vector>

template <typename ElementType, typename ElementIdType> class ElementStorage;
class Texture;
enum class TextureId;

namespace Factory
{
    std::vector<FrameBuffer> MakeFrameBuffers(const ElementStorage<Texture, TextureId>& textureStorage);
}

#endif
