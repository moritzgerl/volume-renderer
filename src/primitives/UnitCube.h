#ifndef UNIT_CUBE_H
#define UNIT_CUBE_H

#include <primitives/UnitCubeVertexCoordinates.h>
#include <buffers/VertexBuffer.h>

// TODO make template class?
class UnitCube
{
public:
    UnitCube();
    void Render() const;

private:
    UnitCubeVertexCoordinates m_vertexCoordinates;
    VertexBuffer m_vertexBuffer;
};

#endif
