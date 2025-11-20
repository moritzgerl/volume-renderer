#include <ssao/SsaoKernel.h>

#include <config/Config.h>


namespace
{
    float Lerp(float a, float b, float f)
    {
        return a + f * (b - a);
    }
}

SsaoKernel::SsaoKernel()
    : m_randomDistribution(0.0, 1.0)
    , m_randomGenerator()
    , m_kernel()
    , m_noise()
{
    UpdateKernel(Config::defaultSsaoKernelSize);
    UpdateNoise(Config::defaultSsaoNoiseSize);
}

const glm::vec3& SsaoKernel::GetSamplePosition(unsigned int i) const
{
    return m_kernel[i];
}

const void* SsaoKernel::GetNoise() const
{
    return &m_noise[0];
}

void SsaoKernel::UpdateKernel(unsigned int kernelSize)
{
    m_kernel.resize(kernelSize);

    for (unsigned int i = 0; i < kernelSize; ++i)
    {
        glm::vec3 sample(m_randomDistribution(m_randomGenerator) * 2.0 - 1.0, m_randomDistribution(m_randomGenerator) * 2.0 - 1.0, m_randomDistribution(m_randomGenerator));
        sample = glm::normalize(sample);
        sample *= m_randomDistribution(m_randomGenerator);
        const float scale = Lerp(0.1f, 1.0f, (float(i) / 64.0f) * (float(i) / 64.0f));
        sample *= scale;
        m_kernel[i] = sample;
    }
}

void SsaoKernel::UpdateNoise(unsigned int noiseSize)
{
    m_noise.resize(noiseSize * noiseSize);

    for (unsigned int i = 0; i < noiseSize * noiseSize; i++)
    {
        const glm::vec3 noise(m_randomDistribution(m_randomGenerator) * 2.0 - 1.0, m_randomDistribution(m_randomGenerator) * 2.0 - 1.0, 0.0f); // rotate around z-axis (in tangent space)
        m_noise[i] = noise;
    }
}