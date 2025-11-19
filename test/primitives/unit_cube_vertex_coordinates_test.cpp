#include <gtest/gtest.h>

#include <primitives/UnitCubeVertexCoordinates.h>

class UnitCubeVertexCoordinatesTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        coords = std::make_unique<UnitCubeVertexCoordinates>();
    }

    std::unique_ptr<UnitCubeVertexCoordinates> coords;
};

TEST_F(UnitCubeVertexCoordinatesTest, CanCreateUnitCubeVertexCoordinates)
{
    EXPECT_NO_THROW(UnitCubeVertexCoordinates());
}

TEST_F(UnitCubeVertexCoordinatesTest, GetReturnsNonNullPointer)
{
    const float* const data = coords->Get();
    EXPECT_NE(data, nullptr);
}

TEST_F(UnitCubeVertexCoordinatesTest, HasCorrectNumberOfVertices)
{
    // Unit cube has 36 vertices (6 faces × 2 triangles × 3 vertices)
    // Each vertex has 6 floats (x, y, z, nx, ny, nz)
    const float* const data = coords->Get();

    // Verify first vertex of first face (back face)
    EXPECT_FLOAT_EQ(data[0], -0.5f);  // x
    EXPECT_FLOAT_EQ(data[1], -0.5f);  // y
    EXPECT_FLOAT_EQ(data[2], -0.5f);  // z
    EXPECT_FLOAT_EQ(data[3],  0.0f);  // nx
    EXPECT_FLOAT_EQ(data[4],  0.0f);  // ny
    EXPECT_FLOAT_EQ(data[5], -1.0f);  // nz
}

TEST_F(UnitCubeVertexCoordinatesTest, BackFaceHasCorrectNormal)
{
    const float* const data = coords->Get();

    // Back face normal should point in -Z direction
    // Check several vertices of the back face
    for (int i = 0; i < 6; ++i)
    {
        const int offset = i * 6;
        EXPECT_FLOAT_EQ(data[offset + 3],  0.0f);  // nx
        EXPECT_FLOAT_EQ(data[offset + 4],  0.0f);  // ny
        EXPECT_FLOAT_EQ(data[offset + 5], -1.0f);  // nz
    }
}

TEST_F(UnitCubeVertexCoordinatesTest, FrontFaceHasCorrectNormal)
{
    const float* const data = coords->Get();

    // Front face starts at vertex 6 (offset 36)
    // Front face normal should point in +Z direction
    for (int i = 6; i < 12; ++i)
    {
        const int offset = i * 6;
        EXPECT_FLOAT_EQ(data[offset + 3], 0.0f);  // nx
        EXPECT_FLOAT_EQ(data[offset + 4], 0.0f);  // ny
        EXPECT_FLOAT_EQ(data[offset + 5], 1.0f);  // nz
    }
}

TEST_F(UnitCubeVertexCoordinatesTest, LeftFaceHasCorrectNormal)
{
    const float* const data = coords->Get();

    // Left face starts at vertex 12 (offset 72)
    // Left face normal should point in -X direction
    for (int i = 12; i < 18; ++i)
    {
        const int offset = i * 6;
        EXPECT_FLOAT_EQ(data[offset + 3], -1.0f);  // nx
        EXPECT_FLOAT_EQ(data[offset + 4],  0.0f);  // ny
        EXPECT_FLOAT_EQ(data[offset + 5],  0.0f);  // nz
    }
}

TEST_F(UnitCubeVertexCoordinatesTest, RightFaceHasCorrectNormal)
{
    const float* const data = coords->Get();

    // Right face starts at vertex 18 (offset 108)
    // Right face normal should point in +X direction
    for (int i = 18; i < 24; ++i)
    {
        const int offset = i * 6;
        EXPECT_FLOAT_EQ(data[offset + 3], 1.0f);  // nx
        EXPECT_FLOAT_EQ(data[offset + 4], 0.0f);  // ny
        EXPECT_FLOAT_EQ(data[offset + 5], 0.0f);  // nz
    }
}

TEST_F(UnitCubeVertexCoordinatesTest, BottomFaceHasCorrectNormal)
{
    const float* const data = coords->Get();

    // Bottom face starts at vertex 24 (offset 144)
    // Bottom face normal should point in -Y direction
    for (int i = 24; i < 30; ++i)
    {
        const int offset = i * 6;
        EXPECT_FLOAT_EQ(data[offset + 3],  0.0f);  // nx
        EXPECT_FLOAT_EQ(data[offset + 4], -1.0f);  // ny
        EXPECT_FLOAT_EQ(data[offset + 5],  0.0f);  // nz
    }
}

TEST_F(UnitCubeVertexCoordinatesTest, TopFaceHasCorrectNormal)
{
    const float* const data = coords->Get();

    // Top face starts at vertex 30 (offset 180)
    // Top face normal should point in +Y direction
    for (int i = 30; i < 36; ++i)
    {
        const int offset = i * 6;
        EXPECT_FLOAT_EQ(data[offset + 3], 0.0f);  // nx
        EXPECT_FLOAT_EQ(data[offset + 4], 1.0f);  // ny
        EXPECT_FLOAT_EQ(data[offset + 5], 0.0f);  // nz
    }
}

TEST_F(UnitCubeVertexCoordinatesTest, VerticesAreWithinUnitCubeBounds)
{
    const float* const data = coords->Get();

    // Check all 36 vertices are within -0.5 to 0.5 range
    for (int i = 0; i < 36; ++i)
    {
        const int offset = i * 6;
        EXPECT_GE(data[offset + 0], -0.5f);  // x >= -0.5
        EXPECT_LE(data[offset + 0],  0.5f);  // x <= 0.5
        EXPECT_GE(data[offset + 1], -0.5f);  // y >= -0.5
        EXPECT_LE(data[offset + 1],  0.5f);  // y <= 0.5
        EXPECT_GE(data[offset + 2], -0.5f);  // z >= -0.5
        EXPECT_LE(data[offset + 2],  0.5f);  // z <= 0.5
    }
}
