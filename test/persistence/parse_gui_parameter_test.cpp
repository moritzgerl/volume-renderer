#include <gtest/gtest.h>

#include <gui/GuiParameters.h>
#include <persistence/ApplicationStateIniFileKey.h>
#include <persistence/ApplicationStateIniFileLoadingError.h>
#include <persistence/ApplicationStateIniFileSection.h>
#include <persistence/ParseGuiParameter.h>

class ParseGuiParameterTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        guiParams = GuiParameters{};
        // Initialize point lights vector with at least 2 lights for testing
        guiParams.pointLights.resize(2);
    }

    GuiParameters guiParams;
};

// Trackball parameters
TEST_F(ParseGuiParameterTest, CanParseTrackballInvertYAxis)
{
    const auto result = Persistence::ParseGuiParameter(
        Persistence::ApplicationStateIniFileSection::Trackball,
        Persistence::ApplicationStateIniFileKey::TrackballInvertYAxis,
        0,
        "1",
        guiParams);

    ASSERT_TRUE(result.has_value());
    EXPECT_TRUE(guiParams.trackballInvertYAxis);
}

TEST_F(ParseGuiParameterTest, CanParseTrackballSensitivity)
{
    const auto result = Persistence::ParseGuiParameter(
        Persistence::ApplicationStateIniFileSection::Trackball,
        Persistence::ApplicationStateIniFileKey::TrackballSensitivity,
        0,
        "0.5",
        guiParams);

    ASSERT_TRUE(result.has_value());
    EXPECT_FLOAT_EQ(guiParams.trackballSensitivity, 0.5f);
}

// SSAO parameters
TEST_F(ParseGuiParameterTest, CanParseSsaoKernelSize)
{
    const auto result = Persistence::ParseGuiParameter(
        Persistence::ApplicationStateIniFileSection::SSAO,
        Persistence::ApplicationStateIniFileKey::SsaoKernelSize,
        0,
        "64",
        guiParams);

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(guiParams.ssaoKernelSize, 64u);
}

TEST_F(ParseGuiParameterTest, CanParseSsaoRadius)
{
    const auto result = Persistence::ParseGuiParameter(
        Persistence::ApplicationStateIniFileSection::SSAO,
        Persistence::ApplicationStateIniFileKey::SsaoRadius,
        0,
        "0.75",
        guiParams);

    ASSERT_TRUE(result.has_value());
    EXPECT_FLOAT_EQ(guiParams.ssaoRadius, 0.75f);
}

TEST_F(ParseGuiParameterTest, CanParseSsaoEnable)
{
    const auto result = Persistence::ParseGuiParameter(
        Persistence::ApplicationStateIniFileSection::SSAO,
        Persistence::ApplicationStateIniFileKey::SsaoEnable,
        0,
        "1",
        guiParams);

    ASSERT_TRUE(result.has_value());
    EXPECT_TRUE(guiParams.enableSsao);
}

// Directional light parameters
TEST_F(ParseGuiParameterTest, CanParseDirectionalLightDirectionX)
{
    const auto result = Persistence::ParseGuiParameter(
        Persistence::ApplicationStateIniFileSection::DirectionalLight,
        Persistence::ApplicationStateIniFileKey::DirectionX,
        0,
        "1.0",
        guiParams);

    ASSERT_TRUE(result.has_value());
    EXPECT_FLOAT_EQ(guiParams.directionalLight.direction.x, 1.0f);
}

TEST_F(ParseGuiParameterTest, CanParseDirectionalLightAmbient)
{
    const auto result = Persistence::ParseGuiParameter(
        Persistence::ApplicationStateIniFileSection::DirectionalLight,
        Persistence::ApplicationStateIniFileKey::AmbientR,
        0,
        "0.2",
        guiParams);

    ASSERT_TRUE(result.has_value());
    EXPECT_FLOAT_EQ(guiParams.directionalLight.ambient.r, 0.2f);
}

TEST_F(ParseGuiParameterTest, CanParseDirectionalLightIntensity)
{
    const auto result = Persistence::ParseGuiParameter(
        Persistence::ApplicationStateIniFileSection::DirectionalLight,
        Persistence::ApplicationStateIniFileKey::Intensity,
        0,
        "1.5",
        guiParams);

    ASSERT_TRUE(result.has_value());
    EXPECT_FLOAT_EQ(guiParams.directionalLight.intensity, 1.5f);
}

// Point light parameters
TEST_F(ParseGuiParameterTest, CanParsePointLightPosition)
{
    const auto result = Persistence::ParseGuiParameter(
        Persistence::ApplicationStateIniFileSection::PointLight,
        Persistence::ApplicationStateIniFileKey::PositionX,
        0,
        "5.0",
        guiParams);

    ASSERT_TRUE(result.has_value());
    EXPECT_FLOAT_EQ(guiParams.pointLights[0].position.x, 5.0f);
}

TEST_F(ParseGuiParameterTest, CanParsePointLightAmbient)
{
    const auto result = Persistence::ParseGuiParameter(
        Persistence::ApplicationStateIniFileSection::PointLight,
        Persistence::ApplicationStateIniFileKey::AmbientG,
        0,
        "0.3",
        guiParams);

    ASSERT_TRUE(result.has_value());
    EXPECT_FLOAT_EQ(guiParams.pointLights[0].ambient.g, 0.3f);
}

TEST_F(ParseGuiParameterTest, CanParsePointLightWithIndex)
{
    const auto result = Persistence::ParseGuiParameter(
        Persistence::ApplicationStateIniFileSection::PointLight,
        Persistence::ApplicationStateIniFileKey::PositionZ,
        1,
        "10.0",
        guiParams);

    ASSERT_TRUE(result.has_value());
    EXPECT_FLOAT_EQ(guiParams.pointLights[1].position.z, 10.0f);
}

// Rendering parameters
TEST_F(ParseGuiParameterTest, CanParseShowLightSources)
{
    const auto result = Persistence::ParseGuiParameter(
        Persistence::ApplicationStateIniFileSection::Rendering,
        Persistence::ApplicationStateIniFileKey::ShowLightSources,
        0,
        "1",
        guiParams);

    ASSERT_TRUE(result.has_value());
    EXPECT_TRUE(guiParams.showLightSources);
}

TEST_F(ParseGuiParameterTest, CanParseDensityMultiplier)
{
    const auto result = Persistence::ParseGuiParameter(
        Persistence::ApplicationStateIniFileSection::Rendering,
        Persistence::ApplicationStateIniFileKey::DensityMultiplier,
        0,
        "2.5",
        guiParams);

    ASSERT_TRUE(result.has_value());
    EXPECT_FLOAT_EQ(guiParams.raycastingDensityMultiplier, 2.5f);
}

// Error handling
TEST_F(ParseGuiParameterTest, ReturnsErrorForInvalidUnsignedInt)
{
    const auto result = Persistence::ParseGuiParameter(
        Persistence::ApplicationStateIniFileSection::SSAO,
        Persistence::ApplicationStateIniFileKey::SsaoKernelSize,
        0,
        "not_a_number",
        guiParams);

    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), Persistence::ApplicationStateIniFileLoadingError::ParseError);
}

TEST_F(ParseGuiParameterTest, ReturnsErrorForInvalidFloat)
{
    const auto result = Persistence::ParseGuiParameter(
        Persistence::ApplicationStateIniFileSection::Trackball,
        Persistence::ApplicationStateIniFileKey::TrackballSensitivity,
        0,
        "invalid",
        guiParams);

    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), Persistence::ApplicationStateIniFileLoadingError::ParseError);
}
