#include <gtest/gtest.h>

#include <primitives/ScreenQuadVertexCoordinates.h>

class ScreenQuadVertexCoordinatesTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        coords = std::make_unique<ScreenQuadVertexCoordinates>();
    }

    std::unique_ptr<ScreenQuadVertexCoordinates> coords;
};

TEST_F(ScreenQuadVertexCoordinatesTest, CanCreateScreenQuadVertexCoordinates)
{
    EXPECT_NO_THROW(ScreenQuadVertexCoordinates());
}

TEST_F(ScreenQuadVertexCoordinatesTest, GetReturnsNonNullPointer)
{
    const float* const data = coords->Get();
    EXPECT_NE(data, nullptr);
}

TEST_F(ScreenQuadVertexCoordinatesTest, HasCorrectNumberOfVertices)
{
    // Screen quad has 4 vertices with 5 floats each (x, y, z, u, v)
    const float* const data = coords->Get();

    // Check first vertex (top-left)
    EXPECT_FLOAT_EQ(data[0], -1.0f);  // x
    EXPECT_FLOAT_EQ(data[1],  1.0f);  // y
    EXPECT_FLOAT_EQ(data[2],  0.0f);  // z
    EXPECT_FLOAT_EQ(data[3],  0.0f);  // u
    EXPECT_FLOAT_EQ(data[4],  1.0f);  // v
}

TEST_F(ScreenQuadVertexCoordinatesTest, HasCorrectBottomLeftVertex)
{
    const float* const data = coords->Get();

    // Second vertex (bottom-left)
    EXPECT_FLOAT_EQ(data[5], -1.0f);  // x
    EXPECT_FLOAT_EQ(data[6], -1.0f);  // y
    EXPECT_FLOAT_EQ(data[7],  0.0f);  // z
    EXPECT_FLOAT_EQ(data[8],  0.0f);  // u
    EXPECT_FLOAT_EQ(data[9],  0.0f);  // v
}

TEST_F(ScreenQuadVertexCoordinatesTest, HasCorrectTopRightVertex)
{
    const float* const data = coords->Get();

    // Third vertex (top-right)
    EXPECT_FLOAT_EQ(data[10],  1.0f);  // x
    EXPECT_FLOAT_EQ(data[11],  1.0f);  // y
    EXPECT_FLOAT_EQ(data[12],  0.0f);  // z
    EXPECT_FLOAT_EQ(data[13],  1.0f);  // u
    EXPECT_FLOAT_EQ(data[14],  1.0f);  // v
}

TEST_F(ScreenQuadVertexCoordinatesTest, HasCorrectBottomRightVertex)
{
    const float* const data = coords->Get();

    // Fourth vertex (bottom-right)
    EXPECT_FLOAT_EQ(data[15],  1.0f);  // x
    EXPECT_FLOAT_EQ(data[16], -1.0f);  // y
    EXPECT_FLOAT_EQ(data[17],  0.0f);  // z
    EXPECT_FLOAT_EQ(data[18],  1.0f);  // u
    EXPECT_FLOAT_EQ(data[19],  0.0f);  // v
}

TEST_F(ScreenQuadVertexCoordinatesTest, CoversNormalizedDeviceCoordinates)
{
    const float* const data = coords->Get();

    // Verify quad covers from -1 to 1 in X and Y
    // Check X coordinates
    EXPECT_FLOAT_EQ(data[0], -1.0f);   // First vertex X
    EXPECT_FLOAT_EQ(data[10], 1.0f);   // Third vertex X

    // Check Y coordinates
    EXPECT_FLOAT_EQ(data[1],  1.0f);   // First vertex Y
    EXPECT_FLOAT_EQ(data[6], -1.0f);   // Second vertex Y
}
