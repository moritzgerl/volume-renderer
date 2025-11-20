#include <gtest/gtest.h>

#include <volumedata/VolumeData.h>
#include <volumedata/VolumeMetadata.h>

class VolumeDataTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        volumeData = VolumeData::VolumeData{};
    }

    VolumeData::VolumeData volumeData;
};

TEST_F(VolumeDataTest, CanCreateDefaultVolumeData)
{
    EXPECT_NO_THROW(VolumeData::VolumeData());
}

TEST_F(VolumeDataTest, CanCreateVolumeDataWithMetadata)
{
    VolumeData::VolumeMetadata metadata{10, 10, 10, 1, 8};
    EXPECT_NO_THROW(VolumeData::VolumeData(metadata));
}

TEST_F(VolumeDataTest, ConstructorWithMetadataAllocatesData)
{
    VolumeData::VolumeMetadata metadata{10, 10, 10, 1, 8};
    VolumeData::VolumeData volume{metadata};

    EXPECT_EQ(volume.GetSizeInBytes(), 1000u);
}

TEST_F(VolumeDataTest, DefaultConstructorDoesNotAllocateData)
{
    EXPECT_EQ(volumeData.GetSizeInBytes(), 0u);
}

TEST_F(VolumeDataTest, GetMetadataReturnsMetadata)
{
    VolumeData::VolumeMetadata metadata{10, 10, 10, 1, 8};
    volumeData.SetMetadata(metadata);

    const VolumeData::VolumeMetadata& retrievedMetadata = volumeData.GetMetadata();
    EXPECT_EQ(retrievedMetadata.GetWidth(), 10u);
    EXPECT_EQ(retrievedMetadata.GetHeight(), 10u);
    EXPECT_EQ(retrievedMetadata.GetDepth(), 10u);
}

TEST_F(VolumeDataTest, CanSetMetadata)
{
    VolumeData::VolumeMetadata metadata{20, 20, 20, 1, 8};
    volumeData.SetMetadata(metadata);

    EXPECT_EQ(volumeData.GetMetadata().GetWidth(), 20u);
}

TEST_F(VolumeDataTest, AllocateDataAllocatesCorrectSize)
{
    VolumeData::VolumeMetadata metadata{10, 10, 10, 1, 8};
    volumeData.SetMetadata(metadata);
    volumeData.AllocateData();

    EXPECT_EQ(volumeData.GetSizeInBytes(), 1000u);
}

TEST_F(VolumeDataTest, AllocateDataWithSizeAllocatesCorrectSize)
{
    volumeData.AllocateData(500);

    EXPECT_EQ(volumeData.GetSizeInBytes(), 500u);
}

TEST_F(VolumeDataTest, GetDataPtrReturnsNonNullAfterAllocation)
{
    volumeData.AllocateData(100);

    EXPECT_NE(volumeData.GetDataPtr(), nullptr);
}

TEST_F(VolumeDataTest, GetDataReturnsVectorReference)
{
    volumeData.AllocateData(10);

    std::vector<uint8_t>& data = volumeData.GetData();
    EXPECT_EQ(data.size(), 10u);
}

TEST_F(VolumeDataTest, IsValidReturnsFalseForDefaultVolumeData)
{
    EXPECT_FALSE(volumeData.IsValid());
}

TEST_F(VolumeDataTest, IsValidReturnsTrueAfterProperInitialization)
{
    VolumeData::VolumeMetadata metadata{10, 10, 10, 1, 8};
    volumeData.SetMetadata(metadata);
    volumeData.AllocateData();

    EXPECT_TRUE(volumeData.IsValid());
}

TEST_F(VolumeDataTest, IsValidReturnsFalseIfDataSizeMismatchesMetadata)
{
    VolumeData::VolumeMetadata metadata{10, 10, 10, 1, 8};
    volumeData.SetMetadata(metadata);
    volumeData.AllocateData(500);  // Wrong size

    EXPECT_FALSE(volumeData.IsValid());
}

TEST_F(VolumeDataTest, ClearRemovesDataAndResetsMetadata)
{
    VolumeData::VolumeMetadata metadata{10, 10, 10, 1, 8};
    volumeData.SetMetadata(metadata);
    volumeData.AllocateData();

    volumeData.Clear();

    EXPECT_EQ(volumeData.GetSizeInBytes(), 0u);
    EXPECT_FALSE(volumeData.IsValid());
}

TEST_F(VolumeDataTest, CanSetAndGetVoxel8)
{
    VolumeData::VolumeMetadata metadata{10, 10, 10, 1, 8};
    VolumeData::VolumeData volume{metadata};

    EXPECT_TRUE(volume.SetVoxel8(5, 5, 5, 128));
    EXPECT_EQ(volume.GetVoxel8(5, 5, 5), 128u);
}

TEST_F(VolumeDataTest, SetVoxel8ReturnsFalseForOutOfBounds)
{
    VolumeData::VolumeMetadata metadata{10, 10, 10, 1, 8};
    VolumeData::VolumeData volume{metadata};

    EXPECT_FALSE(volume.SetVoxel8(10, 5, 5, 128));
    EXPECT_FALSE(volume.SetVoxel8(5, 10, 5, 128));
    EXPECT_FALSE(volume.SetVoxel8(5, 5, 10, 128));
}

TEST_F(VolumeDataTest, GetVoxel8ReturnsZeroForOutOfBounds)
{
    VolumeData::VolumeMetadata metadata{10, 10, 10, 1, 8};
    VolumeData::VolumeData volume{metadata};

    EXPECT_EQ(volume.GetVoxel8(10, 5, 5), 0u);
    EXPECT_EQ(volume.GetVoxel8(5, 10, 5), 0u);
    EXPECT_EQ(volume.GetVoxel8(5, 5, 10), 0u);
}

TEST_F(VolumeDataTest, SetVoxel8ReturnsFalseForNon8BitVolume)
{
    VolumeData::VolumeMetadata metadata{10, 10, 10, 1, 16};
    VolumeData::VolumeData volume{metadata};

    EXPECT_FALSE(volume.SetVoxel8(5, 5, 5, 128));
}

TEST_F(VolumeDataTest, GetVoxel8ReturnsZeroForNon8BitVolume)
{
    VolumeData::VolumeMetadata metadata{10, 10, 10, 1, 16};
    VolumeData::VolumeData volume{metadata};

    EXPECT_EQ(volume.GetVoxel8(5, 5, 5), 0u);
}

TEST_F(VolumeDataTest, CanSetAndGetVoxel16)
{
    VolumeData::VolumeMetadata metadata{10, 10, 10, 1, 16};
    VolumeData::VolumeData volume{metadata};

    EXPECT_TRUE(volume.SetVoxel16(5, 5, 5, 30000));
    EXPECT_EQ(volume.GetVoxel16(5, 5, 5), 30000u);
}

TEST_F(VolumeDataTest, SetVoxel16ReturnsFalseForOutOfBounds)
{
    VolumeData::VolumeMetadata metadata{10, 10, 10, 1, 16};
    VolumeData::VolumeData volume{metadata};

    EXPECT_FALSE(volume.SetVoxel16(10, 5, 5, 30000));
    EXPECT_FALSE(volume.SetVoxel16(5, 10, 5, 30000));
    EXPECT_FALSE(volume.SetVoxel16(5, 5, 10, 30000));
}

TEST_F(VolumeDataTest, GetVoxel16ReturnsZeroForOutOfBounds)
{
    VolumeData::VolumeMetadata metadata{10, 10, 10, 1, 16};
    VolumeData::VolumeData volume{metadata};

    EXPECT_EQ(volume.GetVoxel16(10, 5, 5), 0u);
    EXPECT_EQ(volume.GetVoxel16(5, 10, 5), 0u);
    EXPECT_EQ(volume.GetVoxel16(5, 5, 10), 0u);
}

TEST_F(VolumeDataTest, SetVoxel16ReturnsFalseForNon16BitVolume)
{
    VolumeData::VolumeMetadata metadata{10, 10, 10, 1, 8};
    VolumeData::VolumeData volume{metadata};

    EXPECT_FALSE(volume.SetVoxel16(5, 5, 5, 30000));
}

TEST_F(VolumeDataTest, GetVoxel16ReturnsZeroForNon16BitVolume)
{
    VolumeData::VolumeMetadata metadata{10, 10, 10, 1, 8};
    VolumeData::VolumeData volume{metadata};

    EXPECT_EQ(volume.GetVoxel16(5, 5, 5), 0u);
}

TEST_F(VolumeDataTest, CanSetMultipleVoxels8)
{
    VolumeData::VolumeMetadata metadata{10, 10, 10, 1, 8};
    VolumeData::VolumeData volume{metadata};

    volume.SetVoxel8(0, 0, 0, 10);
    volume.SetVoxel8(9, 9, 9, 20);
    volume.SetVoxel8(5, 5, 5, 30);

    EXPECT_EQ(volume.GetVoxel8(0, 0, 0), 10u);
    EXPECT_EQ(volume.GetVoxel8(9, 9, 9), 20u);
    EXPECT_EQ(volume.GetVoxel8(5, 5, 5), 30u);
}

TEST_F(VolumeDataTest, CanSetMultipleVoxels16)
{
    VolumeData::VolumeMetadata metadata{10, 10, 10, 1, 16};
    VolumeData::VolumeData volume{metadata};

    volume.SetVoxel16(0, 0, 0, 1000);
    volume.SetVoxel16(9, 9, 9, 2000);
    volume.SetVoxel16(5, 5, 5, 3000);

    EXPECT_EQ(volume.GetVoxel16(0, 0, 0), 1000u);
    EXPECT_EQ(volume.GetVoxel16(9, 9, 9), 2000u);
    EXPECT_EQ(volume.GetVoxel16(5, 5, 5), 3000u);
}

TEST_F(VolumeDataTest, VoxelIndexingCoversFullVolume8Bit)
{
    VolumeData::VolumeMetadata metadata{5, 5, 5, 1, 8};
    VolumeData::VolumeData volume{metadata};

    // Set all voxels to different values
    uint8_t value = 0;
    for (uint32_t z = 0; z < 5; ++z)
    {
        for (uint32_t y = 0; y < 5; ++y)
        {
            for (uint32_t x = 0; x < 5; ++x)
            {
                volume.SetVoxel8(x, y, z, value);
                ++value;
            }
        }
    }

    // Verify all voxels
    value = 0;
    for (uint32_t z = 0; z < 5; ++z)
    {
        for (uint32_t y = 0; y < 5; ++y)
        {
            for (uint32_t x = 0; x < 5; ++x)
            {
                EXPECT_EQ(volume.GetVoxel8(x, y, z), value);
                ++value;
            }
        }
    }
}

TEST_F(VolumeDataTest, CanCopyVolumeData)
{
    VolumeData::VolumeMetadata metadata{10, 10, 10, 1, 8};
    VolumeData::VolumeData original{metadata};
    original.SetVoxel8(5, 5, 5, 128);

    VolumeData::VolumeData copy = original;

    EXPECT_EQ(copy.GetVoxel8(5, 5, 5), 128u);
    EXPECT_TRUE(copy.IsValid());
}

TEST_F(VolumeDataTest, CanMoveVolumeData)
{
    VolumeData::VolumeMetadata metadata{10, 10, 10, 1, 8};
    VolumeData::VolumeData original{metadata};
    original.SetVoxel8(5, 5, 5, 128);

    VolumeData::VolumeData moved = std::move(original);

    EXPECT_EQ(moved.GetVoxel8(5, 5, 5), 128u);
    EXPECT_TRUE(moved.IsValid());
}
