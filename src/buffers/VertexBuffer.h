/**
* \file VertexBuffer.h
*
* \brief Vertex buffer object (VBO) abstraction for geometry data.
*/

#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

class ScreenQuadVertexCoordinates;
class UnitCubeVertexCoordinates;

/**
* \class VertexBuffer
*
* \brief Encapsulates OpenGL vertex buffer objects for storing geometry data.
*
* Manages a vertex array object (VAO), vertex buffer object (VBO), and element buffer object (EBO)
* for rendering geometric primitives. Supports initialization from ScreenQuadVertexCoordinates
* or UnitCubeVertexCoordinates.
*
* VertexBuffer is movable but not copyable, following RAII principles with proper cleanup
* in the destructor. Provides methods for binding and unbinding the VAO for rendering.
*
* @see ScreenQuad for screen-aligned quad rendering.
* @see UnitCube for unit cube rendering.
*/
class VertexBuffer
{
public:
    /**
    * Constructor for screen quad geometry.
    * @param screenQuadVertexCoordinates The vertex coordinates for a screen-aligned quad.
    */
    VertexBuffer(const ScreenQuadVertexCoordinates& screenQuadVertexCoordinates);

    /**
    * Constructor for unit cube geometry.
    * @param unitCubeVertexCoordinates The vertex coordinates for a unit cube.
    */
    VertexBuffer(const UnitCubeVertexCoordinates& unitCubeVertexCoordinates);

    // TODO use C++26 concepts
    VertexBuffer(const VertexBuffer&) = delete;
    VertexBuffer(VertexBuffer&& other) noexcept;

    VertexBuffer& operator=(const VertexBuffer&) = delete;
    VertexBuffer& operator=(VertexBuffer&& other) noexcept;

    ~VertexBuffer();

    /**
    * Binds the VAO for rendering.
    * @return void
    */
    void Bind() const;

    /**
    * Unbinds the VAO.
    * @return void
    */
    void Unbind() const;

private:
    unsigned int m_vertexBufferObject; /**< The OpenGL vertex buffer object handle. */
    unsigned int m_vertexArrayObject; /**< The OpenGL vertex array object handle. */
    unsigned int m_elementBufferObject; /**< The OpenGL element buffer object handle. */
};

#endif
