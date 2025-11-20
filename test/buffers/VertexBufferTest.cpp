#include <gtest/gtest.h>

#include <buffers/VertexBuffer.h>
#include <context/InitGl.h>
#include <context/GlfwWindow.h>
#include <primitives/ScreenQuadVertexCoordinates.h>
#include <primitives/UnitCubeVertexCoordinates.h>

#include <memory>

class VertexBufferTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        window = std::make_unique<Context::GlfwWindow>();
        Context::InitGl();

        screenQuadVertexCoordinates = std::make_unique<ScreenQuadVertexCoordinates>();
        unitCubeVertexCoordinates = std::make_unique<UnitCubeVertexCoordinates>();
    }

    void TearDown() override
    {
        screenQuadVertexCoordinates.reset();
        unitCubeVertexCoordinates.reset();
        window.reset();
    }

    std::unique_ptr<ScreenQuadVertexCoordinates> screenQuadVertexCoordinates;
    std::unique_ptr<UnitCubeVertexCoordinates> unitCubeVertexCoordinates;
    std::unique_ptr<Context::GlfwWindow> window;
};

TEST_F(VertexBufferTest, CanCreateVertexBufferWithScreenQuadCoordinates)
{
    EXPECT_NO_THROW(VertexBuffer vertexBuffer(*screenQuadVertexCoordinates));
}

TEST_F(VertexBufferTest, CanCreateVertexBufferWithUnitCubeCoordinates)
{
    EXPECT_NO_THROW(VertexBuffer vertexBuffer(*unitCubeVertexCoordinates));
}

TEST_F(VertexBufferTest, CanBindAndUnbindScreenQuadVertexBuffer)
{
    auto vertexBuffer = VertexBuffer(*screenQuadVertexCoordinates);

    EXPECT_NO_THROW(vertexBuffer.Bind());
    EXPECT_NO_THROW(vertexBuffer.Unbind());
}

TEST_F(VertexBufferTest, CanBindAndUnbindUnitCubeVertexBuffer)
{
    auto vertexBuffer = VertexBuffer(*unitCubeVertexCoordinates);

    EXPECT_NO_THROW(vertexBuffer.Bind());
    EXPECT_NO_THROW(vertexBuffer.Unbind());
}

TEST_F(VertexBufferTest, CanMoveConstructVertexBuffer)
{
    auto vertexBuffer1 = VertexBuffer(*screenQuadVertexCoordinates);

    // Move constructor should not throw
    EXPECT_NO_THROW(auto vertexBuffer2 = std::move(vertexBuffer1));
}

TEST_F(VertexBufferTest, CanMoveAssignVertexBuffer)
{
    auto vertexBuffer1 = VertexBuffer(*screenQuadVertexCoordinates);
    auto vertexBuffer2 = VertexBuffer(*unitCubeVertexCoordinates);

    // Move assignment should not throw
    EXPECT_NO_THROW(vertexBuffer2 = std::move(vertexBuffer1));
}

TEST_F(VertexBufferTest, MovedFromVertexBufferCanBeDestroyed)
{
    auto vertexBuffer1 = VertexBuffer(*screenQuadVertexCoordinates);
    auto vertexBuffer2 = std::move(vertexBuffer1);

    // vertexBuffer1 should be safely destructible after being moved from
    EXPECT_NO_THROW(vertexBuffer1.~VertexBuffer());
}
