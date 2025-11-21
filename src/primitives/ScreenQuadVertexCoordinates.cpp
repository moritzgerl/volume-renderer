#include <primitives/ScreenQuadVertexCoordinates.h>

#include <array>

namespace Constants
{
    constexpr size_t numVertices = 4;
    constexpr size_t floatsPerVertex = 5;
    constexpr size_t sizeInBytes = numVertices * floatsPerVertex * sizeof(float);

    // Normalized Device Coordinates: position (x, y, z), texture coords (u, v)
    constexpr std::array<float, numVertices * floatsPerVertex> vertexCoordinates =
    {
        -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
         1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
         1.0f, -1.0f, 0.0f, 1.0f, 0.0f
    };
}

const float* const ScreenQuadVertexCoordinates::Get() const
{
    return Constants::vertexCoordinates.data();
}

size_t ScreenQuadVertexCoordinates::GetSizeInBytes() const
{
    return Constants::numVertices * Constants::floatsPerVertex * sizeof(float);
}