#include <primitives/ScreenQuadVertexCoordinates.h>

#include <array>

namespace Constants
{
    // Normalized Device Coordinates: position (x, y, z), texture coords (u, v)
    constexpr std::array<float, 20> vertexCoordinates =
    {
        -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
         1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
         1.0f, -1.0f, 0.0f, 1.0f, 0.0f
    };
}

ScreenQuadVertexCoordinates::ScreenQuadVertexCoordinates()

{
}

const float* const ScreenQuadVertexCoordinates::Get() const
{
    return Constants::vertexCoordinates.data();
}
