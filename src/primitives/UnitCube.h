/**
* \file UnitCube.h
*
* \brief Unit cube primitive for volume ray-casting.
*/

#ifndef UNIT_CUBE_H
#define UNIT_CUBE_H

#include <primitives/UnitCubeVertexCoordinates.h>
#include <buffers/VertexBuffer.h>

// TODO make template class?
/**
* \class UnitCube
*
* \brief Renderable unit cube for volume rendering ray entry/exit points.
*
* Provides a cube primitive with vertices at (-0.5, -0.5, -0.5) to (0.5, 0.5, 0.5).
* Used in volume rendering to determine ray entry and exit points by rendering
* the cube's front and back faces.
*
* @see UnitCubeVertexCoordinates for vertex data.
* @see VertexBuffer for OpenGL buffer management.
* @see RenderPass for using the unit cube in volume rendering.
*/
class UnitCube
{
public:
    /**
    * Constructor.
    * Initializes vertex coordinates and uploads them to a vertex buffer.
    */
    UnitCube();

    /**
    * Renders the unit cube.
    * @return void
    */
    void Render() const;

private:
    UnitCubeVertexCoordinates m_vertexCoordinates; /**< Vertex data for the unit cube. */
    VertexBuffer m_vertexBuffer; /**< OpenGL vertex buffer for the cube. */
};

#endif
