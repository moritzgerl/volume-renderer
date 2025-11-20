#include <gtest/gtest.h>

#include <gui/GuiUpdateFlags.h>

class GuiUpdateFlagsTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        flags = GuiUpdateFlags{};
    }

    GuiUpdateFlags flags;
};

TEST_F(GuiUpdateFlagsTest, InitialFlagsAreFalse)
{
    EXPECT_FALSE(flags.ssaoParametersChanged);
    EXPECT_FALSE(flags.transferFunctionChanged);
}

TEST_F(GuiUpdateFlagsTest, CanSetSsaoParametersChangedFlag)
{
    flags.ssaoParametersChanged = true;
    EXPECT_TRUE(flags.ssaoParametersChanged);
    EXPECT_FALSE(flags.transferFunctionChanged);
}

TEST_F(GuiUpdateFlagsTest, CanSetTransferFunctionChangedFlag)
{
    flags.transferFunctionChanged = true;
    EXPECT_TRUE(flags.transferFunctionChanged);
    EXPECT_FALSE(flags.ssaoParametersChanged);
}

TEST_F(GuiUpdateFlagsTest, CanSetMultipleFlags)
{
    flags.ssaoParametersChanged = true;
    flags.transferFunctionChanged = true;

    EXPECT_TRUE(flags.ssaoParametersChanged);
    EXPECT_TRUE(flags.transferFunctionChanged);
}

TEST_F(GuiUpdateFlagsTest, CanClearFlags)
{
    flags.ssaoParametersChanged = true;
    flags.transferFunctionChanged = true;

    flags.ssaoParametersChanged = false;
    flags.transferFunctionChanged = false;

    EXPECT_FALSE(flags.ssaoParametersChanged);
    EXPECT_FALSE(flags.transferFunctionChanged);
}
