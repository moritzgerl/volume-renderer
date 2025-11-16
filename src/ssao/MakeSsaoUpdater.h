/**
* \file MakeSsaoUpdater.h
*
* \brief Factory function for creating the SSAO updater.
*/

#ifndef MAKE_SSAO_UPDATER_H
#define MAKE_SSAO_UPDATER_H

#include <ssao/SsaoUpdater.h>

class Storage;

namespace Factory
{
    /**
    * Creates and initializes the SSAO updater for monitoring parameter changes.
    *
    * Constructs an SsaoUpdater that monitors GuiUpdateFlags for changes to SSAO
    * parameters and regenerates SSAO resources (kernel, noise texture) when needed.
    * The updater automatically updates shader uniforms with new SSAO kernel samples
    * and regenerates the noise texture when the kernel size changes.
    *
    * @param storage Storage containing GUI update flags, SSAO kernel, textures, and shaders.
    * @return Initialized SsaoUpdater object.
    *
    * @see SsaoUpdater for SSAO resource update implementation.
    * @see GuiUpdateFlags for parameter change tracking.
    * @see SsaoKernel for SSAO sample generation.
    */
    SsaoUpdater MakeSsaoUpdater(Storage& storage);
}

#endif
