/**
* \file SsaoKernel.h
*
* \brief SSAO sample kernel and noise texture generation.
*/

#ifndef SSAO_KERNEL_H
#define SSAO_KERNEL_H

#include <glm/glm.hpp>

#include <random>
#include <vector>

/**
* \class SsaoKernel
*
* \brief Generates and manages SSAO sample kernel and noise texture.
*
* Creates a hemisphere-distributed sample kernel for Screen Space Ambient Occlusion
* computation, along with a noise texture for randomizing sample rotation.
* The kernel samples are weighted toward the origin to improve occlusion quality.
*
* Kernel and noise can be regenerated when SSAO parameters change via the GUI.
* SsaoUpdater monitors GuiUpdateFlags and calls UpdateKernel/UpdateNoise as needed.
*
* @see SsaoUpdater for monitoring and triggering updates when parameters change.
* @see GuiParameters for SSAO configuration values (kernel size, noise size).
*/
class SsaoKernel
{
public:
    /**
    * Constructor.
    * Initializes random number generator for kernel and noise generation.
    */
    SsaoKernel();

    /**
    * Retrieves a sample position from the kernel.
    * @param i The sample index.
    * @return const glm::vec3& The sample position vector.
    */
    const glm::vec3& GetSamplePosition(unsigned int i) const;

    /**
    * Retrieves pointer to noise texture data.
    * @return const void* Pointer to noise data for texture upload.
    */
    const void* GetNoise() const;

    /**
    * Regenerates the SSAO kernel with a new size.
    * @param kernelSize The number of samples in the kernel.
    * @return void
    */
    void UpdateKernel(unsigned int kernelSize);

    /**
    * Regenerates the SSAO noise texture with a new size.
    * @param noiseSize The dimensions of the noise texture (noiseSize x noiseSize).
    * @return void
    */
    void UpdateNoise(unsigned int noiseSize);

private:
    std::uniform_real_distribution<float> m_randomDistribution; /**< Random distribution for generating samples. */
    std::default_random_engine m_randomGenerator; /**< Random number generator. */
    std::vector<glm::vec3> m_kernel; /**< Hemisphere-distributed sample positions. */
    std::vector<glm::vec3> m_noise; /**< Random rotation vectors for noise texture. */
};

#endif
