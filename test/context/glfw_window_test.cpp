#include <gtest/gtest.h>

#include <context/GlfwWindow.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <memory>

class GlfwWindowTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        window = std::make_unique<Context::GlfwWindow>();
    }

    void TearDown() override
    {
        window.reset();
    }

    std::unique_ptr<Context::GlfwWindow> window;
};

TEST_F(GlfwWindowTest, WindowIsCreatedSuccessfully)
{
    EXPECT_NE(window->GetWindow().get(), nullptr);
}

TEST_F(GlfwWindowTest, InitialShouldCloseIsFalse)
{
    EXPECT_FALSE(window->ShouldClose());
}

TEST_F(GlfwWindowTest, CanCallPostRender)
{
    // PostRender should not throw
    EXPECT_NO_THROW(window->PostRender());
}

TEST_F(GlfwWindowTest, WindowHasValidContext)
{
    // Verify OpenGL context was created by checking we can query OpenGL state
    GLint major{0};
    GLint minor{0};
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);

    // Expecting OpenGL 3.3 or higher
    EXPECT_GE(major, 3);
    if (major == 3)
    {
        EXPECT_GE(minor, 3);
    }
}

TEST_F(GlfwWindowTest, CanCreateMultipleWindows)
{
    // Create a second window
    auto window2 = std::make_unique<Context::GlfwWindow>();

    EXPECT_NE(window->GetWindow().get(), nullptr);
    EXPECT_NE(window2->GetWindow().get(), nullptr);
    EXPECT_NE(window->GetWindow().get(), window2->GetWindow().get());
}

TEST_F(GlfwWindowTest, WindowCanBeMoved)
{
    auto originalWindowPtr = window->GetWindow().get();

    // Move window to new object
    auto movedWindow = std::move(*window);

    // Moved window should have the same underlying GLFW window
    EXPECT_EQ(movedWindow.GetWindow().get(), originalWindowPtr);
}

TEST_F(GlfwWindowTest, CanSetWindowShouldClose)
{
    // Set window should close flag
    glfwSetWindowShouldClose(window->GetWindow().get(), GLFW_TRUE);

    EXPECT_TRUE(window->ShouldClose());
}
