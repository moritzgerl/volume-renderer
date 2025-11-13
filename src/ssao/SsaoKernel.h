#ifndef SSAO_KERNEL_H
#define SSAO_KERNEL_H

#include <glm/glm.hpp>

#include <random>
#include <vector>

class SsaoKernel
{
public:
    SsaoKernel();
    const glm::vec3& GetSamplePosition(unsigned int i) const;
    const void* GetNoise() const;
    void UpdateKernel(unsigned int kernelSize);
    void UpdateNoise(unsigned int noiseSize);

private:
    std::uniform_real_distribution<float> m_randomDistribution;
    std::default_random_engine m_randomGenerator;
    std::vector<glm::vec3> m_kernel;
    std::vector<glm::vec3> m_noise;
};

#endif
