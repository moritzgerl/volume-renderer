#include <gtest/gtest.h>

#include <context/GlfwWindow.h>
#include <context/InitGl.h>
#include <primitives/ScreenQuad.h>

#include <glad/glad.h>

class ScreenQuadTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        window = std::make_unique<Context::GlfwWindow>();
        Context::InitGl();
        screenQuad = std::make_unique<ScreenQuad>();
    }

    std::unique_ptr<Context::GlfwWindow> window;
    std::unique_ptr<ScreenQuad> screenQuad;
};

TEST_F(ScreenQuadTest, CanCreateScreenQuad)
{
    EXPECT_NO_THROW(ScreenQuad());
}

TEST_F(ScreenQuadTest, CanRenderScreenQuad)
{
    EXPECT_NO_THROW(screenQuad->Render());
}

TEST_F(ScreenQuadTest, RenderDoesNotCauseGLError)
{
    // Clear any existing errors
    while (glGetError() != GL_NO_ERROR);

    screenQuad->Render();

    const GLenum error = glGetError();
    EXPECT_EQ(error, GL_NO_ERROR);
}

TEST_F(ScreenQuadTest, CanCreateMultipleScreenQuads)
{
    ScreenQuad quad1;
    ScreenQuad quad2;
    ScreenQuad quad3;

    EXPECT_NO_THROW(quad1.Render());
    EXPECT_NO_THROW(quad2.Render());
    EXPECT_NO_THROW(quad3.Render());
}
