/**
* \file UnitCubeVertexCoordinates.h
*
* \brief Vertex data for unit cube rendering.
*/

#ifndef UNIT_CUBE_VERTEX_COORDINATES_H
#define UNIT_CUBE_VERTEX_COORDINATES_H

/**
* \class UnitCubeVertexCoordinates
*
* \brief Manages vertex coordinate data for a unit cube.
*
* Provides vertex position data for a cube with vertices at
* (-0.5, -0.5, -0.5) to (0.5, 0.5, 0.5). Used in volume rendering
* to determine ray entry and exit points by rendering the cube's
* front and back faces.
*
* The cube is defined as 36 vertices (6 faces × 2 triangles × 3 vertices),
* with each vertex containing 3D position coordinates and normals.
*
* @see UnitCube for the renderable cube primitive using this data.
* @see VertexBuffer for uploading vertex data to the GPU.
*/
class UnitCubeVertexCoordinates
{
public:
    /**
    * Constructor.
    * Initializes vertex coordinates for a unit cube.
    */
    UnitCubeVertexCoordinates();

    /**
    * Gets a pointer to the vertex coordinate data.
    * @return Const pointer to the raw vertex data array.
    */
    const float* const Get() const;
};

#endif
