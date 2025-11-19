#include <gtest/gtest.h>

#include <camera/CameraParameters.h>
#include <persistence/ApplicationStateIniFileKey.h>
#include <persistence/ApplicationStateIniFileLoadingError.h>
#include <persistence/ParseCameraParameter.h>

class ParseCameraParameterTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        cameraParams = CameraParameters{};
        cameraParams.position = glm::vec3{0.0f, 0.0f, 0.0f};
        cameraParams.zoom = 1.0f;
    }

    CameraParameters cameraParams;
};

TEST_F(ParseCameraParameterTest, CanParsePositionX)
{
    const auto result = Persistence::ParseCameraParameter(
        Persistence::ApplicationStateIniFileKey::PositionX,
        "5.0",
        cameraParams);

    ASSERT_TRUE(result.has_value());
    EXPECT_FLOAT_EQ(cameraParams.position.x, 5.0f);
}

TEST_F(ParseCameraParameterTest, CanParsePositionY)
{
    const auto result = Persistence::ParseCameraParameter(
        Persistence::ApplicationStateIniFileKey::PositionY,
        "10.5",
        cameraParams);

    ASSERT_TRUE(result.has_value());
    EXPECT_FLOAT_EQ(cameraParams.position.y, 10.5f);
}

TEST_F(ParseCameraParameterTest, CanParsePositionZ)
{
    const auto result = Persistence::ParseCameraParameter(
        Persistence::ApplicationStateIniFileKey::PositionZ,
        "-3.25",
        cameraParams);

    ASSERT_TRUE(result.has_value());
    EXPECT_FLOAT_EQ(cameraParams.position.z, -3.25f);
}

TEST_F(ParseCameraParameterTest, CanParseZoom)
{
    const auto result = Persistence::ParseCameraParameter(
        Persistence::ApplicationStateIniFileKey::Zoom,
        "2.5",
        cameraParams);

    ASSERT_TRUE(result.has_value());
    EXPECT_FLOAT_EQ(cameraParams.zoom, 2.5f);
}

TEST_F(ParseCameraParameterTest, CanParseNegativeValues)
{
    const auto result = Persistence::ParseCameraParameter(
        Persistence::ApplicationStateIniFileKey::PositionX,
        "-15.75",
        cameraParams);

    ASSERT_TRUE(result.has_value());
    EXPECT_FLOAT_EQ(cameraParams.position.x, -15.75f);
}

TEST_F(ParseCameraParameterTest, ReturnsErrorForInvalidFloat)
{
    const auto result = Persistence::ParseCameraParameter(
        Persistence::ApplicationStateIniFileKey::Zoom,
        "not_a_number",
        cameraParams);

    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), Persistence::ApplicationStateIniFileLoadingError::ParseError);
}

TEST_F(ParseCameraParameterTest, DoesNotModifyOtherFieldsWhenParsingPositionX)
{
    const glm::vec3 originalPosition = cameraParams.position;
    const float originalZoom = cameraParams.zoom;

    Persistence::ParseCameraParameter(
        Persistence::ApplicationStateIniFileKey::PositionX,
        "100.0",
        cameraParams);

    EXPECT_FLOAT_EQ(cameraParams.position.y, originalPosition.y);
    EXPECT_FLOAT_EQ(cameraParams.position.z, originalPosition.z);
    EXPECT_FLOAT_EQ(cameraParams.zoom, originalZoom);
}
