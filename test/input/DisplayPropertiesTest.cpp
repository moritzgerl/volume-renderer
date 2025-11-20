#include <gtest/gtest.h>

#include <input/DisplayProperties.h>

class DisplayPropertiesTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        displayProperties = DisplayProperties{};
    }

    DisplayProperties displayProperties;
};

TEST_F(DisplayPropertiesTest, CanCreateDefaultDisplayProperties)
{
    EXPECT_NO_THROW(DisplayProperties props{});
}

TEST_F(DisplayPropertiesTest, CanSetShowSsaoMap)
{
    displayProperties.showSsaoMap = true;
    EXPECT_TRUE(displayProperties.showSsaoMap);

    displayProperties.showSsaoMap = false;
    EXPECT_FALSE(displayProperties.showSsaoMap);
}

TEST_F(DisplayPropertiesTest, CanToggleSsaoMap)
{
    const bool initialValue = displayProperties.showSsaoMap;
    displayProperties.showSsaoMap = !displayProperties.showSsaoMap;
    EXPECT_NE(displayProperties.showSsaoMap, initialValue);

    displayProperties.showSsaoMap = !displayProperties.showSsaoMap;
    EXPECT_EQ(displayProperties.showSsaoMap, initialValue);
}
