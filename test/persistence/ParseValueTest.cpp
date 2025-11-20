#include <gtest/gtest.h>

#include <persistence/ApplicationStateIniFileLoadingError.h>
#include <persistence/ParseValue.h>

class ParseValueTest : public ::testing::Test
{
};

TEST_F(ParseValueTest, CanParseUnsignedInt)
{
    const auto result = Persistence::ParseValue<unsigned int>("42");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(*result, 42u);
}

TEST_F(ParseValueTest, CanParseZeroUnsignedInt)
{
    const auto result = Persistence::ParseValue<unsigned int>("0");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(*result, 0u);
}

TEST_F(ParseValueTest, CanParseLargeUnsignedInt)
{
    const auto result = Persistence::ParseValue<unsigned int>("4294967295");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(*result, 4294967295u);
}

TEST_F(ParseValueTest, ReturnsErrorForNegativeUnsignedInt)
{
    const auto result = Persistence::ParseValue<unsigned int>("-1");
    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), Persistence::ApplicationStateIniFileLoadingError::ParseError);
}

TEST_F(ParseValueTest, ReturnsErrorForInvalidUnsignedInt)
{
    const auto result = Persistence::ParseValue<unsigned int>("not_a_number");
    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), Persistence::ApplicationStateIniFileLoadingError::ParseError);
}

TEST_F(ParseValueTest, CanParseFloat)
{
    const auto result = Persistence::ParseValue<float>("3.14");
    ASSERT_TRUE(result.has_value());
    EXPECT_FLOAT_EQ(*result, 3.14f);
}

TEST_F(ParseValueTest, CanParseNegativeFloat)
{
    const auto result = Persistence::ParseValue<float>("-2.5");
    ASSERT_TRUE(result.has_value());
    EXPECT_FLOAT_EQ(*result, -2.5f);
}

TEST_F(ParseValueTest, CanParseZeroFloat)
{
    const auto result = Persistence::ParseValue<float>("0.0");
    ASSERT_TRUE(result.has_value());
    EXPECT_FLOAT_EQ(*result, 0.0f);
}

TEST_F(ParseValueTest, CanParseIntegerAsFloat)
{
    const auto result = Persistence::ParseValue<float>("5");
    ASSERT_TRUE(result.has_value());
    EXPECT_FLOAT_EQ(*result, 5.0f);
}

TEST_F(ParseValueTest, ReturnsErrorForInvalidFloat)
{
    const auto result = Persistence::ParseValue<float>("not_a_float");
    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), Persistence::ApplicationStateIniFileLoadingError::ParseError);
}

TEST_F(ParseValueTest, ReturnsErrorForEmptyString)
{
    const auto result = Persistence::ParseValue<unsigned int>("");
    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), Persistence::ApplicationStateIniFileLoadingError::ParseError);
}
