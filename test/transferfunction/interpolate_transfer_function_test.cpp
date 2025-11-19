#include <gtest/gtest.h>

#include <transferfunction/InterpolateTransferFunction.h>
#include <transferfunction/TransferFunctionControlPoint.h>

#include <glm/glm.hpp>
#include <span>
#include <vector>

class InterpolateTransferFunctionTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        controlPoints.clear();
    }

    std::vector<TransferFunctionControlPoint> controlPoints;
};

TEST_F(InterpolateTransferFunctionTest, ReturnsTransparentBlackWithNoControlPoints)
{
    const glm::vec4 result = InterpolateTransferFunction(0.5f, std::span<const TransferFunctionControlPoint>{});

    EXPECT_EQ(result, glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
}

TEST_F(InterpolateTransferFunctionTest, ReturnsSingleControlPointColorWithOnePoint)
{
    controlPoints.push_back(TransferFunctionControlPoint{0.5f, glm::vec3{1.0f, 0.0f, 0.0f}, 0.8f});

    const glm::vec4 result = InterpolateTransferFunction(0.3f, controlPoints);

    EXPECT_EQ(result.r, 1.0f);
    EXPECT_EQ(result.g, 0.0f);
    EXPECT_EQ(result.b, 0.0f);
    EXPECT_EQ(result.a, 0.8f);
}

TEST_F(InterpolateTransferFunctionTest, ReturnsFirstControlPointBeforeRange)
{
    controlPoints.push_back(TransferFunctionControlPoint{0.3f, glm::vec3{1.0f, 0.0f, 0.0f}, 0.5f});
    controlPoints.push_back(TransferFunctionControlPoint{0.7f, glm::vec3{0.0f, 0.0f, 1.0f}, 0.9f});

    const glm::vec4 result = InterpolateTransferFunction(0.1f, controlPoints);

    EXPECT_EQ(result.r, 1.0f);
    EXPECT_EQ(result.g, 0.0f);
    EXPECT_EQ(result.b, 0.0f);
    EXPECT_EQ(result.a, 0.5f);
}

TEST_F(InterpolateTransferFunctionTest, ReturnsLastControlPointAfterRange)
{
    controlPoints.push_back(TransferFunctionControlPoint{0.3f, glm::vec3{1.0f, 0.0f, 0.0f}, 0.5f});
    controlPoints.push_back(TransferFunctionControlPoint{0.7f, glm::vec3{0.0f, 0.0f, 1.0f}, 0.9f});

    const glm::vec4 result = InterpolateTransferFunction(0.9f, controlPoints);

    EXPECT_EQ(result.r, 0.0f);
    EXPECT_EQ(result.g, 0.0f);
    EXPECT_EQ(result.b, 1.0f);
    EXPECT_EQ(result.a, 0.9f);
}

TEST_F(InterpolateTransferFunctionTest, InterpolatesColorBetweenTwoPoints)
{
    controlPoints.push_back(TransferFunctionControlPoint{0.0f, glm::vec3{1.0f, 0.0f, 0.0f}, 0.0f});
    controlPoints.push_back(TransferFunctionControlPoint{1.0f, glm::vec3{0.0f, 0.0f, 1.0f}, 1.0f});

    const glm::vec4 result = InterpolateTransferFunction(0.5f, controlPoints);

    // Color should be interpolated (linear interpolation)
    EXPECT_NEAR(result.r, 0.5f, 0.01f);
    EXPECT_NEAR(result.g, 0.0f, 0.01f);
    EXPECT_NEAR(result.b, 0.5f, 0.01f);
}

TEST_F(InterpolateTransferFunctionTest, InterpolatesOpacityWithCatmullRom)
{
    // Create 4 control points for Catmull-Rom interpolation
    controlPoints.push_back(TransferFunctionControlPoint{0.0f, glm::vec3{1.0f, 0.0f, 0.0f}, 0.0f});
    controlPoints.push_back(TransferFunctionControlPoint{0.33f, glm::vec3{0.0f, 1.0f, 0.0f}, 0.5f});
    controlPoints.push_back(TransferFunctionControlPoint{0.67f, glm::vec3{0.0f, 0.0f, 1.0f}, 0.5f});
    controlPoints.push_back(TransferFunctionControlPoint{1.0f, glm::vec3{1.0f, 1.0f, 1.0f}, 1.0f});

    const glm::vec4 result = InterpolateTransferFunction(0.5f, controlPoints);

    // Opacity should be interpolated with Catmull-Rom spline
    EXPECT_TRUE(std::isfinite(result.a));
    EXPECT_GE(result.a, 0.0f);
    EXPECT_LE(result.a, 1.0f);
}

TEST_F(InterpolateTransferFunctionTest, HandlesMultipleControlPoints)
{
    controlPoints.push_back(TransferFunctionControlPoint{0.0f, glm::vec3{1.0f, 0.0f, 0.0f}, 0.0f});
    controlPoints.push_back(TransferFunctionControlPoint{0.25f, glm::vec3{0.0f, 1.0f, 0.0f}, 0.3f});
    controlPoints.push_back(TransferFunctionControlPoint{0.5f, glm::vec3{0.0f, 0.0f, 1.0f}, 0.6f});
    controlPoints.push_back(TransferFunctionControlPoint{0.75f, glm::vec3{1.0f, 1.0f, 0.0f}, 0.9f});
    controlPoints.push_back(TransferFunctionControlPoint{1.0f, glm::vec3{1.0f, 1.0f, 1.0f}, 1.0f});

    const glm::vec4 result = InterpolateTransferFunction(0.6f, controlPoints);

    EXPECT_TRUE(std::isfinite(result.r));
    EXPECT_TRUE(std::isfinite(result.g));
    EXPECT_TRUE(std::isfinite(result.b));
    EXPECT_TRUE(std::isfinite(result.a));
}

TEST_F(InterpolateTransferFunctionTest, ReturnsValidResultAtExactControlPointValue)
{
    controlPoints.push_back(TransferFunctionControlPoint{0.3f, glm::vec3{1.0f, 0.0f, 0.0f}, 0.5f});
    controlPoints.push_back(TransferFunctionControlPoint{0.7f, glm::vec3{0.0f, 0.0f, 1.0f}, 0.9f});

    const glm::vec4 result = InterpolateTransferFunction(0.3f, controlPoints);

    EXPECT_TRUE(std::isfinite(result.r));
    EXPECT_TRUE(std::isfinite(result.g));
    EXPECT_TRUE(std::isfinite(result.b));
    EXPECT_TRUE(std::isfinite(result.a));
}

TEST_F(InterpolateTransferFunctionTest, HandlesBoundaryValues)
{
    controlPoints.push_back(TransferFunctionControlPoint{0.0f, glm::vec3{1.0f, 0.0f, 0.0f}, 0.0f});
    controlPoints.push_back(TransferFunctionControlPoint{1.0f, glm::vec3{0.0f, 0.0f, 1.0f}, 1.0f});

    const glm::vec4 result0 = InterpolateTransferFunction(0.0f, controlPoints);
    const glm::vec4 result1 = InterpolateTransferFunction(1.0f, controlPoints);

    EXPECT_TRUE(std::isfinite(result0.r));
    EXPECT_TRUE(std::isfinite(result0.a));
    EXPECT_TRUE(std::isfinite(result1.r));
    EXPECT_TRUE(std::isfinite(result1.a));
}

TEST_F(InterpolateTransferFunctionTest, HandlesCloselySpacedControlPoints)
{
    controlPoints.push_back(TransferFunctionControlPoint{0.5f, glm::vec3{1.0f, 0.0f, 0.0f}, 0.5f});
    controlPoints.push_back(TransferFunctionControlPoint{0.51f, glm::vec3{0.0f, 0.0f, 1.0f}, 0.6f});

    const glm::vec4 result = InterpolateTransferFunction(0.505f, controlPoints);

    EXPECT_TRUE(std::isfinite(result.r));
    EXPECT_TRUE(std::isfinite(result.g));
    EXPECT_TRUE(std::isfinite(result.b));
    EXPECT_TRUE(std::isfinite(result.a));
}

TEST_F(InterpolateTransferFunctionTest, ColorInterpolationIsLinear)
{
    controlPoints.push_back(TransferFunctionControlPoint{0.0f, glm::vec3{0.0f, 0.0f, 0.0f}, 0.0f});
    controlPoints.push_back(TransferFunctionControlPoint{1.0f, glm::vec3{1.0f, 1.0f, 1.0f}, 1.0f});

    const glm::vec4 result = InterpolateTransferFunction(0.5f, controlPoints);

    // Linear interpolation means color should be exactly halfway
    EXPECT_NEAR(result.r, 0.5f, 0.01f);
    EXPECT_NEAR(result.g, 0.5f, 0.01f);
    EXPECT_NEAR(result.b, 0.5f, 0.01f);
}
