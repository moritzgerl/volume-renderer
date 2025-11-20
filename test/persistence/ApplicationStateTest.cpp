#include <gtest/gtest.h>

#include <persistence/ApplicationState.h>

class ApplicationStateTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        state = Persistence::ApplicationState{};
    }

    Persistence::ApplicationState state;
};

TEST_F(ApplicationStateTest, CanCreateDefaultApplicationState)
{
    EXPECT_NO_THROW(Persistence::ApplicationState defaultState{});
}

TEST_F(ApplicationStateTest, CanAccessCameraParameters)
{
    state.cameraParameters.position = glm::vec3{1.0f, 2.0f, 3.0f};
    EXPECT_EQ(state.cameraParameters.position, glm::vec3(1.0f, 2.0f, 3.0f));
}

TEST_F(ApplicationStateTest, CanAccessGuiParameters)
{
    state.guiParameters.ssaoKernelSize = 64;
    EXPECT_EQ(state.guiParameters.ssaoKernelSize, 64u);
}
