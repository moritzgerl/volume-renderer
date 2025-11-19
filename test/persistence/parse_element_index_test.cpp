#include <gtest/gtest.h>

#include <persistence/ApplicationStateIniFileLoadingError.h>
#include <persistence/ApplicationStateIniFileSection.h>
#include <persistence/ParseElementIndex.h>

class ParseElementIndexTest : public ::testing::Test
{
};

// TransferFunctionPoint section tests
TEST_F(ParseElementIndexTest, CanParseTransferFunctionPointIndex0)
{
    const auto result = Persistence::ParseElementIndex(
        "[TransferFunctionPoint0]",
        Persistence::ApplicationStateIniFileSection::TransferFunctionPoint);

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(*result, 0u);
}

TEST_F(ParseElementIndexTest, CanParseTransferFunctionPointIndex5)
{
    const auto result = Persistence::ParseElementIndex(
        "[TransferFunctionPoint5]",
        Persistence::ApplicationStateIniFileSection::TransferFunctionPoint);

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(*result, 5u);
}

TEST_F(ParseElementIndexTest, CanParseTransferFunctionPointLargeIndex)
{
    const auto result = Persistence::ParseElementIndex(
        "[TransferFunctionPoint999]",
        Persistence::ApplicationStateIniFileSection::TransferFunctionPoint);

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(*result, 999u);
}

// PointLight section tests
TEST_F(ParseElementIndexTest, CanParsePointLightIndex0)
{
    const auto result = Persistence::ParseElementIndex(
        "[PointLight0]",
        Persistence::ApplicationStateIniFileSection::PointLight);

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(*result, 0u);
}

TEST_F(ParseElementIndexTest, CanParsePointLightIndex3)
{
    const auto result = Persistence::ParseElementIndex(
        "[PointLight3]",
        Persistence::ApplicationStateIniFileSection::PointLight);

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(*result, 3u);
}

TEST_F(ParseElementIndexTest, CanParsePointLightLargeIndex)
{
    const auto result = Persistence::ParseElementIndex(
        "[PointLight100]",
        Persistence::ApplicationStateIniFileSection::PointLight);

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(*result, 100u);
}

// Error handling tests
TEST_F(ParseElementIndexTest, ReturnsErrorForNonIndexedSection)
{
    const auto result = Persistence::ParseElementIndex(
        "[Camera]",
        Persistence::ApplicationStateIniFileSection::Camera);

    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), Persistence::ApplicationStateIniFileLoadingError::ParseError);
}

TEST_F(ParseElementIndexTest, ReturnsErrorForMissingClosingBracket)
{
    const auto result = Persistence::ParseElementIndex(
        "[PointLight5",
        Persistence::ApplicationStateIniFileSection::PointLight);

    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), Persistence::ApplicationStateIniFileLoadingError::ParseError);
}

TEST_F(ParseElementIndexTest, ReturnsErrorForEmptyIndex)
{
    const auto result = Persistence::ParseElementIndex(
        "[PointLight]",
        Persistence::ApplicationStateIniFileSection::PointLight);

    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), Persistence::ApplicationStateIniFileLoadingError::ParseError);
}

TEST_F(ParseElementIndexTest, ReturnsErrorForInvalidIndex)
{
    const auto result = Persistence::ParseElementIndex(
        "[PointLightabc]",
        Persistence::ApplicationStateIniFileSection::PointLight);

    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), Persistence::ApplicationStateIniFileLoadingError::ParseError);
}

TEST_F(ParseElementIndexTest, ReturnsErrorForNegativeIndex)
{
    const auto result = Persistence::ParseElementIndex(
        "[PointLight-1]",
        Persistence::ApplicationStateIniFileSection::PointLight);

    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), Persistence::ApplicationStateIniFileLoadingError::ParseError);
}

TEST_F(ParseElementIndexTest, ReturnsErrorForTooShortLine)
{
    const auto result = Persistence::ParseElementIndex(
        "[PointLight",
        Persistence::ApplicationStateIniFileSection::PointLight);

    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), Persistence::ApplicationStateIniFileLoadingError::ParseError);
}
