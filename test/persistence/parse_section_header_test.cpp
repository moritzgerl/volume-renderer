#include <gtest/gtest.h>

#include <persistence/ApplicationStateIniFileSection.h>
#include <persistence/ParseSectionHeader.h>

class ParseSectionHeaderTest : public ::testing::Test
{
};

TEST_F(ParseSectionHeaderTest, CanParseCameraSection)
{
    const auto result = Persistence::ParseSectionHeader("[Camera]");
    EXPECT_EQ(result, Persistence::ApplicationStateIniFileSection::Camera);
}

TEST_F(ParseSectionHeaderTest, CanParseGuiParametersSection)
{
    const auto result = Persistence::ParseSectionHeader("[GuiParameters]");
    EXPECT_EQ(result, Persistence::ApplicationStateIniFileSection::GuiParameters);
}

TEST_F(ParseSectionHeaderTest, CanParseTransferFunctionSection)
{
    const auto result = Persistence::ParseSectionHeader("[TransferFunction]");
    EXPECT_EQ(result, Persistence::ApplicationStateIniFileSection::TransferFunction);
}

TEST_F(ParseSectionHeaderTest, CanParseTrackballSection)
{
    const auto result = Persistence::ParseSectionHeader("[Trackball]");
    EXPECT_EQ(result, Persistence::ApplicationStateIniFileSection::Trackball);
}

TEST_F(ParseSectionHeaderTest, CanParseSsaoSection)
{
    const auto result = Persistence::ParseSectionHeader("[SSAO]");
    EXPECT_EQ(result, Persistence::ApplicationStateIniFileSection::SSAO);
}

TEST_F(ParseSectionHeaderTest, CanParseDirectionalLightSection)
{
    const auto result = Persistence::ParseSectionHeader("[DirectionalLight]");
    EXPECT_EQ(result, Persistence::ApplicationStateIniFileSection::DirectionalLight);
}

TEST_F(ParseSectionHeaderTest, CanParseRenderingSection)
{
    const auto result = Persistence::ParseSectionHeader("[Rendering]");
    EXPECT_EQ(result, Persistence::ApplicationStateIniFileSection::Rendering);
}

TEST_F(ParseSectionHeaderTest, CanParseTransferFunctionPointSection)
{
    const auto result = Persistence::ParseSectionHeader("[TransferFunctionPoint:0]");
    EXPECT_EQ(result, Persistence::ApplicationStateIniFileSection::TransferFunctionPoint);
}

TEST_F(ParseSectionHeaderTest, CanParsePointLightSection)
{
    const auto result = Persistence::ParseSectionHeader("[PointLight:0]");
    EXPECT_EQ(result, Persistence::ApplicationStateIniFileSection::PointLight);
}

TEST_F(ParseSectionHeaderTest, ReturnsNoneForUnknownSection)
{
    const auto result = Persistence::ParseSectionHeader("[UnknownSection]");
    EXPECT_EQ(result, Persistence::ApplicationStateIniFileSection::None);
}

TEST_F(ParseSectionHeaderTest, ReturnsNoneForInvalidFormat)
{
    const auto result = Persistence::ParseSectionHeader("NotASection");
    EXPECT_EQ(result, Persistence::ApplicationStateIniFileSection::None);
}
