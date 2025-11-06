#ifndef UNIT_CUBE_H
#define UNIT_CUBE_H

#include <primitives/UnitCubeVertexCoordinates.h>
#include <buffers/VertexBuffer.h>

#include <memory>

class UnitCube
{
public:
    UnitCube();
    void Render() const;

private:
    UnitCubeVertexCoordinates m_vertexCoordinates;
    std::unique_ptr<VertexBuffer> m_vertexBuffer;
};

#endif
