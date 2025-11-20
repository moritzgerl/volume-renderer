#include <gtest/gtest.h>

#include <volumedata/VolumeMetadata.h>

using namespace VolumeData;

class VolumeMetadataTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        metadata = VolumeMetadata{};
    }

    VolumeMetadata metadata;
};

TEST_F(VolumeMetadataTest, CanCreateDefaultVolumeMetadata)
{
    EXPECT_NO_THROW(VolumeMetadata());
}

TEST_F(VolumeMetadataTest, DefaultConstructorInitializesWithZeroDimensions)
{
    EXPECT_EQ(metadata.GetWidth(), 0u);
    EXPECT_EQ(metadata.GetHeight(), 0u);
    EXPECT_EQ(metadata.GetDepth(), 0u);
}

TEST_F(VolumeMetadataTest, DefaultConstructorInitializesWithDefaultComponents)
{
    EXPECT_EQ(metadata.GetComponents(), 1u);
    EXPECT_EQ(metadata.GetBitsPerComponent(), 8u);
}

TEST_F(VolumeMetadataTest, DefaultConstructorInitializesWithUniformScale)
{
    EXPECT_EQ(metadata.GetScaleX(), 1.0f);
    EXPECT_EQ(metadata.GetScaleY(), 1.0f);
    EXPECT_EQ(metadata.GetScaleZ(), 1.0f);
}

TEST_F(VolumeMetadataTest, CanCreateVolumeMetadataWithParameters)
{
    VolumeMetadata meta{256, 256, 128, 1, 8};

    EXPECT_EQ(meta.GetWidth(), 256u);
    EXPECT_EQ(meta.GetHeight(), 256u);
    EXPECT_EQ(meta.GetDepth(), 128u);
    EXPECT_EQ(meta.GetComponents(), 1u);
    EXPECT_EQ(meta.GetBitsPerComponent(), 8u);
}

TEST_F(VolumeMetadataTest, ParameterizedConstructorInitializesWithUniformScale)
{
    VolumeMetadata meta{100, 100, 100, 1, 8};

    EXPECT_EQ(meta.GetScaleX(), 1.0f);
    EXPECT_EQ(meta.GetScaleY(), 1.0f);
    EXPECT_EQ(meta.GetScaleZ(), 1.0f);
}

TEST_F(VolumeMetadataTest, CanSetWidth)
{
    metadata.SetWidth(512);
    EXPECT_EQ(metadata.GetWidth(), 512u);
}

TEST_F(VolumeMetadataTest, CanSetHeight)
{
    metadata.SetHeight(256);
    EXPECT_EQ(metadata.GetHeight(), 256u);
}

TEST_F(VolumeMetadataTest, CanSetDepth)
{
    metadata.SetDepth(128);
    EXPECT_EQ(metadata.GetDepth(), 128u);
}

TEST_F(VolumeMetadataTest, CanSetComponents)
{
    metadata.SetComponents(2);
    EXPECT_EQ(metadata.GetComponents(), 2u);
}

TEST_F(VolumeMetadataTest, CanSetBitsPerComponent)
{
    metadata.SetBitsPerComponent(16);
    EXPECT_EQ(metadata.GetBitsPerComponent(), 16u);
}

TEST_F(VolumeMetadataTest, CanSetScaleX)
{
    metadata.SetScaleX(2.0f);
    EXPECT_EQ(metadata.GetScaleX(), 2.0f);
}

TEST_F(VolumeMetadataTest, CanSetScaleY)
{
    metadata.SetScaleY(1.5f);
    EXPECT_EQ(metadata.GetScaleY(), 1.5f);
}

TEST_F(VolumeMetadataTest, CanSetScaleZ)
{
    metadata.SetScaleZ(0.5f);
    EXPECT_EQ(metadata.GetScaleZ(), 0.5f);
}

TEST_F(VolumeMetadataTest, CanSetAllScales)
{
    metadata.SetScale(2.0f, 1.5f, 0.5f);

    EXPECT_EQ(metadata.GetScaleX(), 2.0f);
    EXPECT_EQ(metadata.GetScaleY(), 1.5f);
    EXPECT_EQ(metadata.GetScaleZ(), 0.5f);
}

TEST_F(VolumeMetadataTest, GetVoxelCountReturnsCorrectValue)
{
    metadata.SetWidth(10);
    metadata.SetHeight(20);
    metadata.SetDepth(30);

    EXPECT_EQ(metadata.GetVoxelCount(), 10u * 20u * 30u);
}

TEST_F(VolumeMetadataTest, GetBytesPerVoxelReturnsCorrectValueFor8Bit)
{
    metadata.SetComponents(1);
    metadata.SetBitsPerComponent(8);

    EXPECT_EQ(metadata.GetBytesPerVoxel(), 1u);
}

TEST_F(VolumeMetadataTest, GetBytesPerVoxelReturnsCorrectValueFor16Bit)
{
    metadata.SetComponents(1);
    metadata.SetBitsPerComponent(16);

    EXPECT_EQ(metadata.GetBytesPerVoxel(), 2u);
}

TEST_F(VolumeMetadataTest, GetBytesPerVoxelReturnsCorrectValueForMultipleComponents)
{
    metadata.SetComponents(3);
    metadata.SetBitsPerComponent(8);

    EXPECT_EQ(metadata.GetBytesPerVoxel(), 3u);
}

TEST_F(VolumeMetadataTest, GetTotalSizeInBytesReturnsCorrectValue)
{
    metadata.SetWidth(10);
    metadata.SetHeight(10);
    metadata.SetDepth(10);
    metadata.SetComponents(1);
    metadata.SetBitsPerComponent(8);

    EXPECT_EQ(metadata.GetTotalSizeInBytes(), 1000u);
}

TEST_F(VolumeMetadataTest, GetTotalSizeInBytesReturnsCorrectValueFor16Bit)
{
    metadata.SetWidth(10);
    metadata.SetHeight(10);
    metadata.SetDepth(10);
    metadata.SetComponents(1);
    metadata.SetBitsPerComponent(16);

    EXPECT_EQ(metadata.GetTotalSizeInBytes(), 2000u);
}

TEST_F(VolumeMetadataTest, IsValidReturnsFalseForDefault)
{
    EXPECT_FALSE(metadata.IsValid());
}

TEST_F(VolumeMetadataTest, IsValidReturnsTrueForValidMetadata)
{
    metadata.SetWidth(256);
    metadata.SetHeight(256);
    metadata.SetDepth(128);
    metadata.SetComponents(1);
    metadata.SetBitsPerComponent(8);

    EXPECT_TRUE(metadata.IsValid());
}

TEST_F(VolumeMetadataTest, IsValidReturnsFalseForZeroWidth)
{
    metadata.SetWidth(0);
    metadata.SetHeight(256);
    metadata.SetDepth(128);
    metadata.SetComponents(1);
    metadata.SetBitsPerComponent(8);

    EXPECT_FALSE(metadata.IsValid());
}

TEST_F(VolumeMetadataTest, IsValidReturnsFalseForZeroHeight)
{
    metadata.SetWidth(256);
    metadata.SetHeight(0);
    metadata.SetDepth(128);
    metadata.SetComponents(1);
    metadata.SetBitsPerComponent(8);

    EXPECT_FALSE(metadata.IsValid());
}

TEST_F(VolumeMetadataTest, IsValidReturnsFalseForZeroDepth)
{
    metadata.SetWidth(256);
    metadata.SetHeight(256);
    metadata.SetDepth(0);
    metadata.SetComponents(1);
    metadata.SetBitsPerComponent(8);

    EXPECT_FALSE(metadata.IsValid());
}

TEST_F(VolumeMetadataTest, IsValidReturnsFalseForZeroComponents)
{
    metadata.SetWidth(256);
    metadata.SetHeight(256);
    metadata.SetDepth(128);
    metadata.SetComponents(0);
    metadata.SetBitsPerComponent(8);

    EXPECT_FALSE(metadata.IsValid());
}

TEST_F(VolumeMetadataTest, IsValidReturnsFalseForZeroBitsPerComponent)
{
    metadata.SetWidth(256);
    metadata.SetHeight(256);
    metadata.SetDepth(128);
    metadata.SetComponents(1);
    metadata.SetBitsPerComponent(0);

    EXPECT_FALSE(metadata.IsValid());
}

TEST_F(VolumeMetadataTest, IsValidReturnsFalseForNonByteAlignedBits)
{
    metadata.SetWidth(256);
    metadata.SetHeight(256);
    metadata.SetDepth(128);
    metadata.SetComponents(1);
    metadata.SetBitsPerComponent(7);

    EXPECT_FALSE(metadata.IsValid());
}

TEST_F(VolumeMetadataTest, IsValidReturnsTrueFor16BitComponents)
{
    metadata.SetWidth(256);
    metadata.SetHeight(256);
    metadata.SetDepth(128);
    metadata.SetComponents(1);
    metadata.SetBitsPerComponent(16);

    EXPECT_TRUE(metadata.IsValid());
}

TEST_F(VolumeMetadataTest, CanCreateLargeVolume)
{
    VolumeMetadata large{1024, 1024, 512, 1, 8};

    EXPECT_EQ(large.GetVoxelCount(), 1024u * 1024u * 512u);
    EXPECT_TRUE(large.IsValid());
}
