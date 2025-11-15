/**
* \file SsaoUpdater.h
*
* \brief Monitors and updates SSAO resources when parameters change.
*/

#ifndef SSAO_UPDATER_H
#define SSAO_UPDATER_H

struct GuiParameters;
struct GuiUpdateFlags;
class SsaoKernel;
class Shader;
class Texture;

/**
* \class SsaoUpdater
*
* \brief Updates SSAO kernel, noise texture, and shader uniforms when parameters change.
*
* Monitors GuiUpdateFlags to detect when SSAO parameters (kernel size, sample radius)
* have been modified via the GUI. When changes are detected, regenerates the SSAO
* kernel samples, updates the noise texture, and passes new parameters to the SSAO
* shaders.
*
* The updater modifies resources in Storage via reference and clears the update flag
* after processing. This prevents unnecessary regeneration when parameters are stable.
*
* @see SsaoKernel for hemisphere sample generation.
* @see GuiUpdateFlags for change detection.
* @see GuiParameters for SSAO parameter storage.
* @see Shader for shader uniform updates.
*/
class SsaoUpdater
{
public:
    /**
    * Constructor.
    * @param guiUpdateFlags Reference to GUI update flags for change detection.
    * @param guiParameters Reference to GUI parameters containing SSAO settings.
    * @param ssaoKernel Reference to SSAO kernel to regenerate when parameters change.
    * @param ssaoNoiseTexture Reference to noise texture to update.
    * @param ssaoShader Reference to SSAO shader for uniform updates.
    * @param ssaoFinalShader Reference to SSAO final compositing shader for uniform updates.
    */
    SsaoUpdater(
        GuiUpdateFlags& guiUpdateFlags,
        const GuiParameters& guiParameters,
        SsaoKernel& ssaoKernel,
        Texture& ssaoNoiseTexture,
        const Shader& ssaoShader,
        const Shader& ssaoFinalShader
    );

    /**
    * Checks for SSAO parameter changes and updates resources if needed.
    * Should be called once per frame before rendering.
    * @return void
    */
    void Update();

private:
    /**
    * Regenerates the SSAO noise texture based on current kernel.
    */
    void UpdateSsaoNoiseTexture();

    /**
    * Updates SSAO shader uniforms with current kernel samples and parameters.
    */
    void UpdateSsaoShader();

    /**
    * Updates SSAO final shader uniforms with current parameters.
    */
    void UpdateSsaoFinalShader();

private:
    GuiUpdateFlags& m_guiUpdateFlags; /**< Reference to GUI update flags. */
    const GuiParameters& m_guiParameters; /**< Reference to GUI parameters with SSAO settings. */
    SsaoKernel& m_ssaoKernel; /**< Reference to SSAO kernel for regeneration. */
    Texture& m_ssaoNoiseTexture; /**< Reference to noise texture to update. */
    const Shader& m_ssaoShader; /**< Reference to SSAO shader for uniform updates. */
    const Shader& m_ssaoFinalShader; /**< Reference to SSAO final shader for uniform updates. */
};

#endif
