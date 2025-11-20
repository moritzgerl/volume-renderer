#include <gtest/gtest.h>

#include <buffers/FrameBuffer.h>
#include <context/InitGl.h>
#include <context/GlfwWindow.h>

#include <glad/glad.h>

#include <memory>

class FrameBufferTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        window = std::make_unique<Context::GlfwWindow>();
        Context::InitGl();

        frameBufferId = FrameBufferId::Ssao;
        frameBuffer = std::make_unique<FrameBuffer>(frameBufferId);
    }

    void TearDown() override
    {
        frameBuffer.reset();
        window.reset();
    }

    FrameBufferId frameBufferId;
    std::unique_ptr<FrameBuffer> frameBuffer;
    std::unique_ptr<Context::GlfwWindow> window;
};

TEST_F(FrameBufferTest, IsFrameBufferIdInitializedCorrectly)
{
    EXPECT_EQ(frameBuffer->GetId(), frameBufferId);
}

TEST_F(FrameBufferTest, IsDefaultFrameBufferIdCorrect)
{
    const auto defaultFrameBufferId = FrameBufferId::Default;
    const auto defaultFrameBuffer = FrameBuffer(defaultFrameBufferId);

    EXPECT_EQ(defaultFrameBuffer.GetId(), defaultFrameBufferId);
}

TEST_F(FrameBufferTest, CanBindAndUnbindFrameBuffer)
{
    // This test verifies that Bind() and Unbind() don't throw exceptions
    // Actual OpenGL state verification would require querying GL state
    EXPECT_NO_THROW(frameBuffer->Bind());
    EXPECT_NO_THROW(frameBuffer->Unbind());
}

TEST_F(FrameBufferTest, CanAttachRenderBuffer)
{
    const unsigned int width = 800;
    const unsigned int height = 600;

    frameBuffer->Bind();

    // Attach a depth-stencil renderbuffer
    EXPECT_NO_THROW(frameBuffer->AttachRenderBuffer(GL_DEPTH_STENCIL_ATTACHMENT, GL_DEPTH24_STENCIL8, width, height));

    frameBuffer->Unbind();
}
