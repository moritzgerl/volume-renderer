#include <gtest/gtest.h>

#include <config/Config.h>
#include <ssao/SsaoKernel.h>

#include <glm/glm.hpp>

class SsaoKernelTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        kernel = std::make_unique<SsaoKernel>();
    }

    std::unique_ptr<SsaoKernel> kernel;
};

TEST_F(SsaoKernelTest, CanCreateSsaoKernel)
{
    EXPECT_NO_THROW(SsaoKernel());
}

TEST_F(SsaoKernelTest, GetSamplePositionReturnsValidVector)
{
    const glm::vec3& sample = kernel->GetSamplePosition(0);
    EXPECT_TRUE(std::isfinite(sample.x));
    EXPECT_TRUE(std::isfinite(sample.y));
    EXPECT_TRUE(std::isfinite(sample.z));
}

TEST_F(SsaoKernelTest, GetNoiseReturnsNonNullPointer)
{
    const void* noise = kernel->GetNoise();
    EXPECT_NE(noise, nullptr);
}

TEST_F(SsaoKernelTest, CanUpdateKernelWithDifferentSize)
{
    EXPECT_NO_THROW(kernel->UpdateKernel(32));
    EXPECT_NO_THROW(kernel->UpdateKernel(128));
}

TEST_F(SsaoKernelTest, CanUpdateNoiseWithDifferentSize)
{
    EXPECT_NO_THROW(kernel->UpdateNoise(2));
    EXPECT_NO_THROW(kernel->UpdateNoise(8));
}

TEST_F(SsaoKernelTest, UpdateKernelGeneratesValidSamples)
{
    kernel->UpdateKernel(16);

    for (unsigned int i = 0; i < 16; ++i)
    {
        const glm::vec3& sample = kernel->GetSamplePosition(i);
        EXPECT_TRUE(std::isfinite(sample.x));
        EXPECT_TRUE(std::isfinite(sample.y));
        EXPECT_TRUE(std::isfinite(sample.z));
    }
}

TEST_F(SsaoKernelTest, KernelSamplesAreInHemisphere)
{
    kernel->UpdateKernel(64);

    for (unsigned int i = 0; i < 64; ++i)
    {
        const glm::vec3& sample = kernel->GetSamplePosition(i);
        // Z component should be non-negative (hemisphere samples)
        EXPECT_GE(sample.z, 0.0f);
    }
}

TEST_F(SsaoKernelTest, KernelSamplesHaveReasonableLength)
{
    kernel->UpdateKernel(64);

    for (unsigned int i = 0; i < 64; ++i)
    {
        const glm::vec3& sample = kernel->GetSamplePosition(i);
        float length = glm::length(sample);
        // Samples should be reasonably close to the origin (weighted toward center)
        EXPECT_GE(length, 0.0f);
        EXPECT_LE(length, 1.0f);
    }
}

TEST_F(SsaoKernelTest, CanUpdateKernelMultipleTimes)
{
    kernel->UpdateKernel(32);
    kernel->UpdateKernel(64);
    kernel->UpdateKernel(128);

    const glm::vec3& sample = kernel->GetSamplePosition(0);
    EXPECT_TRUE(std::isfinite(sample.x));
}

TEST_F(SsaoKernelTest, CanUpdateNoiseMultipleTimes)
{
    kernel->UpdateNoise(2);
    kernel->UpdateNoise(4);
    kernel->UpdateNoise(8);

    const void* noise = kernel->GetNoise();
    EXPECT_NE(noise, nullptr);
}

TEST_F(SsaoKernelTest, UpdateKernelWithZeroSize)
{
    // Should handle edge case of zero-sized kernel
    EXPECT_NO_THROW(kernel->UpdateKernel(0));
}

TEST_F(SsaoKernelTest, UpdateNoiseWithZeroSize)
{
    // Should handle edge case of zero-sized noise
    EXPECT_NO_THROW(kernel->UpdateNoise(0));
}

TEST_F(SsaoKernelTest, UpdateKernelWithLargeSize)
{
    // Should handle large kernel sizes
    EXPECT_NO_THROW(kernel->UpdateKernel(256));
}

TEST_F(SsaoKernelTest, UpdateNoiseWithLargeSize)
{
    // Should handle large noise sizes
    EXPECT_NO_THROW(kernel->UpdateNoise(16));
}

TEST_F(SsaoKernelTest, DefaultConstructorUsesConfigValues)
{
    SsaoKernel defaultKernel;

    // After default construction, should be able to access samples up to default size
    EXPECT_NO_THROW(defaultKernel.GetSamplePosition(0));
    EXPECT_NO_THROW(defaultKernel.GetSamplePosition(Config::defaultSsaoKernelSize - 1));
}
