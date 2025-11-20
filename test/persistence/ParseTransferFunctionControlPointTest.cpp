#include <gtest/gtest.h>

#include <persistence/ApplicationStateIniFileKey.h>
#include <persistence/ApplicationStateIniFileLoadingError.h>
#include <persistence/ParseTransferFunctionControlPoint.h>
#include <transferfunction/TransferFunctionControlPoint.h>

class ParseTransferFunctionControlPointTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        point = TransferFunctionControlPoint{};
        point.value = 0.0f;
        point.color = glm::vec3{0.0f, 0.0f, 0.0f};
        point.opacity = 0.0f;
    }

    TransferFunctionControlPoint point;
};

TEST_F(ParseTransferFunctionControlPointTest, CanParseValue)
{
    const auto result = Persistence::ParseTransferFunctionControlPoint(
        Persistence::ApplicationStateIniFileKey::Value,
        "0.75",
        point);

    ASSERT_TRUE(result.has_value());
    EXPECT_FLOAT_EQ(point.value, 0.75f);
}

TEST_F(ParseTransferFunctionControlPointTest, CanParseColorR)
{
    const auto result = Persistence::ParseTransferFunctionControlPoint(
        Persistence::ApplicationStateIniFileKey::ColorR,
        "1.0",
        point);

    ASSERT_TRUE(result.has_value());
    EXPECT_FLOAT_EQ(point.color.r, 1.0f);
}

TEST_F(ParseTransferFunctionControlPointTest, CanParseColorG)
{
    const auto result = Persistence::ParseTransferFunctionControlPoint(
        Persistence::ApplicationStateIniFileKey::ColorG,
        "0.5",
        point);

    ASSERT_TRUE(result.has_value());
    EXPECT_FLOAT_EQ(point.color.g, 0.5f);
}

TEST_F(ParseTransferFunctionControlPointTest, CanParseColorB)
{
    const auto result = Persistence::ParseTransferFunctionControlPoint(
        Persistence::ApplicationStateIniFileKey::ColorB,
        "0.25",
        point);

    ASSERT_TRUE(result.has_value());
    EXPECT_FLOAT_EQ(point.color.b, 0.25f);
}

TEST_F(ParseTransferFunctionControlPointTest, CanParseOpacity)
{
    const auto result = Persistence::ParseTransferFunctionControlPoint(
        Persistence::ApplicationStateIniFileKey::Opacity,
        "0.8",
        point);

    ASSERT_TRUE(result.has_value());
    EXPECT_FLOAT_EQ(point.opacity, 0.8f);
}

TEST_F(ParseTransferFunctionControlPointTest, ReturnsErrorForInvalidFloat)
{
    const auto result = Persistence::ParseTransferFunctionControlPoint(
        Persistence::ApplicationStateIniFileKey::Value,
        "invalid",
        point);

    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), Persistence::ApplicationStateIniFileLoadingError::ParseError);
}

TEST_F(ParseTransferFunctionControlPointTest, DoesNotModifyOtherFieldsWhenParsingColorR)
{
    const float originalValue = point.value;
    const glm::vec3 originalColor = point.color;
    const float originalOpacity = point.opacity;

    Persistence::ParseTransferFunctionControlPoint(
        Persistence::ApplicationStateIniFileKey::ColorR,
        "0.9",
        point);

    EXPECT_FLOAT_EQ(point.value, originalValue);
    EXPECT_FLOAT_EQ(point.color.g, originalColor.g);
    EXPECT_FLOAT_EQ(point.color.b, originalColor.b);
    EXPECT_FLOAT_EQ(point.opacity, originalOpacity);
}
