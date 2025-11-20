#include <gtest/gtest.h>

#include <persistence/ApplicationStateIniFileLoadingError.h>
#include <persistence/ParseKeyValuePair.h>

class ParseKeyValuePairTest : public ::testing::Test
{
};

TEST_F(ParseKeyValuePairTest, CanParseSimpleKeyValuePair)
{
    const auto result = Persistence::ParseKeyValuePair("key=value");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->key, "key");
    EXPECT_EQ(result->value, "value");
}

TEST_F(ParseKeyValuePairTest, CanParseKeyValuePairWithSpaces)
{
    const auto result = Persistence::ParseKeyValuePair("key = value");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->key, "key");
    EXPECT_EQ(result->value, "value");
}

TEST_F(ParseKeyValuePairTest, CanParseKeyValuePairWithLeadingAndTrailingSpaces)
{
    const auto result = Persistence::ParseKeyValuePair("  key  =  value  ");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->key, "key");
    EXPECT_EQ(result->value, "value");
}

TEST_F(ParseKeyValuePairTest, CanParseKeyValuePairWithTabs)
{
    const auto result = Persistence::ParseKeyValuePair("\tkey\t=\tvalue\t");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->key, "key");
    EXPECT_EQ(result->value, "value");
}

TEST_F(ParseKeyValuePairTest, CanParseEmptyValue)
{
    const auto result = Persistence::ParseKeyValuePair("key=");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->key, "key");
    EXPECT_TRUE(result->value.empty());
}

TEST_F(ParseKeyValuePairTest, ReturnsErrorWhenNoEqualSign)
{
    const auto result = Persistence::ParseKeyValuePair("keyvalue");
    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), Persistence::ApplicationStateIniFileLoadingError::ParseError);
}

TEST_F(ParseKeyValuePairTest, ReturnsErrorWhenKeyIsEmpty)
{
    const auto result = Persistence::ParseKeyValuePair("=value");
    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), Persistence::ApplicationStateIniFileLoadingError::ParseError);
}

TEST_F(ParseKeyValuePairTest, ReturnsErrorWhenKeyIsOnlyWhitespace)
{
    const auto result = Persistence::ParseKeyValuePair("   =value");
    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), Persistence::ApplicationStateIniFileLoadingError::ParseError);
}

TEST_F(ParseKeyValuePairTest, CanParseValueWithMultipleEqualSigns)
{
    const auto result = Persistence::ParseKeyValuePair("key=value=another");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->key, "key");
    EXPECT_EQ(result->value, "value=another");
}
