#include <gtest/gtest.h>

#include <volumedata/GetVolumeMetadataKey.h>
#include <volumedata/VolumeMetadataKey.h>

using namespace VolumeData;

TEST(GetVolumeMetadataKeyTest, CanConvertWidthString)
{
    const VolumeMetadataKey key = GetVolumeMetadataKey("Width");
    EXPECT_EQ(key, VolumeMetadataKey::Width);
}

TEST(GetVolumeMetadataKeyTest, CanConvertHeightString)
{
    const VolumeMetadataKey key = GetVolumeMetadataKey("Height");
    EXPECT_EQ(key, VolumeMetadataKey::Height);
}

TEST(GetVolumeMetadataKeyTest, CanConvertDepthString)
{
    const VolumeMetadataKey key = GetVolumeMetadataKey("Depth");
    EXPECT_EQ(key, VolumeMetadataKey::Depth);
}

TEST(GetVolumeMetadataKeyTest, CanConvertComponentsString)
{
    const VolumeMetadataKey key = GetVolumeMetadataKey("Components");
    EXPECT_EQ(key, VolumeMetadataKey::Components);
}

TEST(GetVolumeMetadataKeyTest, CanConvertBitsPerComponentString)
{
    const VolumeMetadataKey key = GetVolumeMetadataKey("BitsPerComponent");
    EXPECT_EQ(key, VolumeMetadataKey::BitsPerComponent);
}

TEST(GetVolumeMetadataKeyTest, CanConvertScaleXString)
{
    const VolumeMetadataKey key = GetVolumeMetadataKey("ScaleX");
    EXPECT_EQ(key, VolumeMetadataKey::ScaleX);
}

TEST(GetVolumeMetadataKeyTest, CanConvertScaleYString)
{
    const VolumeMetadataKey key = GetVolumeMetadataKey("ScaleY");
    EXPECT_EQ(key, VolumeMetadataKey::ScaleY);
}

TEST(GetVolumeMetadataKeyTest, CanConvertScaleZString)
{
    const VolumeMetadataKey key = GetVolumeMetadataKey("ScaleZ");
    EXPECT_EQ(key, VolumeMetadataKey::ScaleZ);
}

TEST(GetVolumeMetadataKeyTest, ReturnsUnknownForUnrecognizedString)
{
    const VolumeMetadataKey key = GetVolumeMetadataKey("InvalidKey");
    EXPECT_EQ(key, VolumeMetadataKey::Unknown);
}

TEST(GetVolumeMetadataKeyTest, ReturnsUnknownForEmptyString)
{
    const VolumeMetadataKey key = GetVolumeMetadataKey("");
    EXPECT_EQ(key, VolumeMetadataKey::Unknown);
}

TEST(GetVolumeMetadataKeyTest, IsCaseSensitive)
{
    const VolumeMetadataKey lowercase = GetVolumeMetadataKey("width");
    const VolumeMetadataKey uppercase = GetVolumeMetadataKey("WIDTH");

    EXPECT_EQ(lowercase, VolumeMetadataKey::Unknown);
    EXPECT_EQ(uppercase, VolumeMetadataKey::Unknown);
}

TEST(GetVolumeMetadataKeyTest, DoesNotMatchPartialStrings)
{
    const VolumeMetadataKey key = GetVolumeMetadataKey("Wid");
    EXPECT_EQ(key, VolumeMetadataKey::Unknown);
}

TEST(GetVolumeMetadataKeyTest, DoesNotMatchWithExtraCharacters)
{
    const VolumeMetadataKey key = GetVolumeMetadataKey("Width ");
    EXPECT_EQ(key, VolumeMetadataKey::Unknown);
}

TEST(GetVolumeMetadataKeyTest, HandlesAllValidKeys)
{
    EXPECT_NE(GetVolumeMetadataKey("Width"), VolumeMetadataKey::Unknown);
    EXPECT_NE(GetVolumeMetadataKey("Height"), VolumeMetadataKey::Unknown);
    EXPECT_NE(GetVolumeMetadataKey("Depth"), VolumeMetadataKey::Unknown);
    EXPECT_NE(GetVolumeMetadataKey("Components"), VolumeMetadataKey::Unknown);
    EXPECT_NE(GetVolumeMetadataKey("BitsPerComponent"), VolumeMetadataKey::Unknown);
    EXPECT_NE(GetVolumeMetadataKey("ScaleX"), VolumeMetadataKey::Unknown);
    EXPECT_NE(GetVolumeMetadataKey("ScaleY"), VolumeMetadataKey::Unknown);
    EXPECT_NE(GetVolumeMetadataKey("ScaleZ"), VolumeMetadataKey::Unknown);
}
