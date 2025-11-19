#include <gtest/gtest.h>

#include <context/GlfwWindow.h>
#include <context/InitGl.h>
#include <primitives/UnitCube.h>

#include <glad/glad.h>

class UnitCubeTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        window = std::make_unique<Context::GlfwWindow>();
        Context::InitGl();
        unitCube = std::make_unique<UnitCube>();
    }

    std::unique_ptr<Context::GlfwWindow> window;
    std::unique_ptr<UnitCube> unitCube;
};

TEST_F(UnitCubeTest, CanCreateUnitCube)
{
    EXPECT_NO_THROW(UnitCube());
}

TEST_F(UnitCubeTest, CanRenderUnitCube)
{
    EXPECT_NO_THROW(unitCube->Render());
}

TEST_F(UnitCubeTest, RenderDoesNotCauseGLError)
{
    // Clear any existing errors
    while (glGetError() != GL_NO_ERROR);

    unitCube->Render();

    const GLenum error = glGetError();
    EXPECT_EQ(error, GL_NO_ERROR);
}

TEST_F(UnitCubeTest, CanCreateMultipleUnitCubes)
{
    UnitCube cube1;
    UnitCube cube2;
    UnitCube cube3;

    EXPECT_NO_THROW(cube1.Render());
    EXPECT_NO_THROW(cube2.Render());
    EXPECT_NO_THROW(cube3.Render());
}
