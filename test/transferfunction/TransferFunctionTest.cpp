#include <gtest/gtest.h>

#include <transferfunction/TransferFunction.h>
#include <transferfunction/TransferFunctionControlPoint.h>

#include <glm/glm.hpp>

class TransferFunctionTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        transferFunction = TransferFunction{};
    }

    TransferFunction transferFunction;
};

TEST_F(TransferFunctionTest, CanCreateTransferFunction)
{
    EXPECT_NO_THROW(TransferFunction());
}

TEST_F(TransferFunctionTest, GetNumActivePointsReturnsZeroByDefault)
{
    const size_t numPoints = transferFunction.GetNumActivePoints();
    EXPECT_EQ(numPoints, 0u);
}

TEST_F(TransferFunctionTest, CanSetNumActivePoints)
{
    transferFunction.SetNumActivePoints(5);
    EXPECT_EQ(transferFunction.GetNumActivePoints(), 5u);
}

TEST_F(TransferFunctionTest, SetNumActivePointsClampsToMax)
{
    transferFunction.SetNumActivePoints(100);
    EXPECT_EQ(transferFunction.GetNumActivePoints(), TransferFunctionConstants::maxNumControlPoints);
}

TEST_F(TransferFunctionTest, CanIncrementNumActivePoints)
{
    transferFunction.SetNumActivePoints(3);
    transferFunction.IncrementNumActivePoints();
    EXPECT_EQ(transferFunction.GetNumActivePoints(), 4u);
}

TEST_F(TransferFunctionTest, IncrementNumActivePointsDoesNotExceedMax)
{
    transferFunction.SetNumActivePoints(TransferFunctionConstants::maxNumControlPoints);
    transferFunction.IncrementNumActivePoints();
    EXPECT_EQ(transferFunction.GetNumActivePoints(), TransferFunctionConstants::maxNumControlPoints);
}

TEST_F(TransferFunctionTest, CanGetControlPointsConst)
{
    const TransferFunction& constTf = transferFunction;
    EXPECT_NO_THROW(constTf.GetControlPoints());
}

TEST_F(TransferFunctionTest, CanGetControlPointsMutable)
{
    EXPECT_NO_THROW(transferFunction.GetControlPoints());
}

TEST_F(TransferFunctionTest, CanAccessControlPointViaOperator)
{
    transferFunction.SetNumActivePoints(1);
    transferFunction[0].value = 0.5f;
    transferFunction[0].opacity = 0.8f;
    transferFunction[0].color = glm::vec3{1.0f, 0.0f, 0.0f};

    EXPECT_EQ(transferFunction[0].value, 0.5f);
    EXPECT_EQ(transferFunction[0].opacity, 0.8f);
    EXPECT_EQ(transferFunction[0].color, glm::vec3(1.0f, 0.0f, 0.0f));
}

TEST_F(TransferFunctionTest, CanAccessControlPointViaOperatorConst)
{
    transferFunction.SetNumActivePoints(1);
    transferFunction[0].value = 0.3f;

    const TransferFunction& constTf = transferFunction;
    EXPECT_EQ(constTf[0].value, 0.3f);
}

TEST_F(TransferFunctionTest, CanAddPoint)
{
    transferFunction.AddPoint(0.5f, 0.8f);
    EXPECT_EQ(transferFunction.GetNumActivePoints(), 1u);
    EXPECT_EQ(transferFunction[0].value, 0.5f);
    EXPECT_EQ(transferFunction[0].opacity, 0.8f);
}

TEST_F(TransferFunctionTest, AddPointMaintainsSortedOrder)
{
    transferFunction.AddPoint(0.5f, 0.5f);
    transferFunction.AddPoint(0.2f, 0.3f);
    transferFunction.AddPoint(0.8f, 0.7f);

    EXPECT_EQ(transferFunction.GetNumActivePoints(), 3u);
    EXPECT_LT(transferFunction[0].value, transferFunction[1].value);
    EXPECT_LT(transferFunction[1].value, transferFunction[2].value);
}

TEST_F(TransferFunctionTest, AddPointInterpolatesColorBetweenPoints)
{
    // Add three points in order first
    transferFunction.AddPoint(0.0f, 0.5f);
    transferFunction.AddPoint(0.5f, 0.5f);
    transferFunction.AddPoint(1.0f, 0.5f);

    // Set colors on endpoints
    transferFunction[0].color = glm::vec3{1.0f, 0.0f, 0.0f};
    transferFunction[2].color = glm::vec3{0.0f, 0.0f, 1.0f};

    // Remove middle point and re-add to trigger interpolation
    transferFunction.RemovePoint(1);
    transferFunction.AddPoint(0.5f, 0.5f);

    // Middle point should have interpolated color between red and blue
    const glm::vec3& middleColor = transferFunction[1].color;
    EXPECT_GT(middleColor.r, 0.0f);
    EXPECT_GT(middleColor.b, 0.0f);
}

TEST_F(TransferFunctionTest, CanRemovePoint)
{
    transferFunction.AddPoint(0.5f, 0.5f);
    transferFunction.AddPoint(0.3f, 0.3f);

    EXPECT_EQ(transferFunction.GetNumActivePoints(), 2u);

    transferFunction.RemovePoint(0);

    EXPECT_EQ(transferFunction.GetNumActivePoints(), 1u);
    EXPECT_EQ(transferFunction[0].value, 0.5f);
}

TEST_F(TransferFunctionTest, RemovePointShiftsRemainingPoints)
{
    transferFunction.AddPoint(0.2f, 0.2f);
    transferFunction.AddPoint(0.5f, 0.5f);
    transferFunction.AddPoint(0.8f, 0.8f);

    transferFunction.RemovePoint(1);

    EXPECT_EQ(transferFunction.GetNumActivePoints(), 2u);
    EXPECT_EQ(transferFunction[0].value, 0.2f);
    EXPECT_EQ(transferFunction[1].value, 0.8f);
}

TEST_F(TransferFunctionTest, CanAddMultiplePoints)
{
    for (size_t i = 0; i < 5; ++i)
    {
        transferFunction.AddPoint(static_cast<float>(i) / 10.0f, 0.5f);
    }

    EXPECT_EQ(transferFunction.GetNumActivePoints(), 5u);
}

TEST_F(TransferFunctionTest, CanRemoveMultiplePoints)
{
    transferFunction.AddPoint(0.2f, 0.2f);
    transferFunction.AddPoint(0.4f, 0.4f);
    transferFunction.AddPoint(0.6f, 0.6f);

    transferFunction.RemovePoint(0);
    transferFunction.RemovePoint(0);

    EXPECT_EQ(transferFunction.GetNumActivePoints(), 1u);
    EXPECT_EQ(transferFunction[0].value, 0.6f);
}
