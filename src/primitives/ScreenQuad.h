/**
* \file ScreenQuad.h
*
* \brief Screen-aligned quad primitive for full-screen rendering passes.
*/

#ifndef SCREEN_QUAD_H
#define SCREEN_QUAD_H

#include <primitives/ScreenQuadVertexCoordinates.h>
#include <buffers/VertexBuffer.h>

/**
* \class ScreenQuad
*
* \brief Renderable screen-aligned quad covering the entire viewport.
*
* Provides a simple quad primitive that covers the full screen for rendering
* full-screen passes such as SSAO, blur, and final compositing. The quad is
* defined in normalized device coordinates (-1 to 1).
*
* @see ScreenQuadVertexCoordinates for vertex data.
* @see VertexBuffer for OpenGL buffer management.
* @see RenderPass for using the screen quad in rendering stages.
*/
class ScreenQuad
{
public:
    /**
    * Constructor.
    * Initializes vertex coordinates and uploads them to a vertex buffer.
    */
    ScreenQuad();

    /**
    * Renders the screen quad.
    * @return void
    */
    void Render() const;

private:
    ScreenQuadVertexCoordinates m_vertexCoordinates; /**< Vertex data for the screen quad. */
    VertexBuffer m_vertexBuffer; /**< OpenGL vertex buffer for the quad. */
};

#endif
