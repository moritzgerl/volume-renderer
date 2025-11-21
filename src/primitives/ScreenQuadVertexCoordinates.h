/**
* \file ScreenQuadVertexCoordinates.h
*
* \brief Vertex data for screen-aligned quad rendering.
*/

#ifndef SCREEN_QUAD_VERTEX_COORDINATES_H
#define SCREEN_QUAD_VERTEX_COORDINATES_H

/**
* \class ScreenQuadVertexCoordinates
*
* \brief Manages vertex coordinate data for a full-screen quad.
*
* Provides vertex position and texture coordinate data for a screen-aligned
* quad covering the entire viewport. The quad is defined in normalized device
* coordinates (NDC) from (-1, -1) to (1, 1).
*
* Each vertex contains position (x, y, z) and texture coordinates (u, v),
* arranged as two triangles forming a rectangle.
*
* @see ScreenQuad for the renderable quad primitive using this data.
* @see VertexBuffer for uploading vertex data to the GPU.
*/
class ScreenQuadVertexCoordinates
{
public:
    /**
    * Constructor.
    * Initializes vertex coordinates for a full-screen quad.
    */
    ScreenQuadVertexCoordinates();

    /**
    * Gets a pointer to the vertex coordinate data.
    * @return Const pointer to the raw vertex data array.
    */
    const float* const Get() const;
};

#endif
