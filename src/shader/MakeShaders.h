/**
* \file MakeShaders.h
*
* \brief Factory function for creating and configuring all shader programs.
*/

#ifndef MAKE_SHADERS_H
#define MAKE_SHADERS_H

#include <shader/Shader.h>
#include <storage/StorageTypes.h>
#include <vector>

struct GuiParameters;
class SsaoKernel;

namespace Factory
{
    /**
    * Creates and initializes all shader programs for the rendering pipeline.
    *
    * Compiles and links shader programs for all rendering passes including
    * volume rendering, SSAO computation, SSAO blur, SSAO final composition,
    * light source visualization, and debug visualization. Each shader is
    * configured with initial uniform values from GUI parameters, SSAO kernel,
    * and texture bindings. The shaders are indexed by ShaderId enum values.
    *
    * @param guiParameters GUI parameters containing initial shader uniform values.
    * @param ssaoKernel SSAO kernel containing sample positions for ambient occlusion.
    * @param textureStorage Storage containing texture resources for shader binding.
    * @return Vector of configured Shader objects indexed by ShaderId.
    *
    * @see Shader for shader program abstraction.
    * @see ShaderId for shader identifier enumeration.
    * @see GuiParameters for runtime shader parameters.
    * @see SsaoKernel for SSAO sample generation.
    */
    std::vector<Shader> MakeShaders(
        const GuiParameters& guiParameters,
        const SsaoKernel& ssaoKernel,
        const TextureStorage& textureStorage
    );
}

#endif
