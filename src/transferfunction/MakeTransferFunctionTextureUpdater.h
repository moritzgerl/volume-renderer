/**
* \file MakeTransferFunctionTextureUpdater.h
*
* \brief Factory function for creating the transfer function texture updater.
*/

#ifndef MAKE_TRANSFER_FUNCTION_TEXTURE_UPDATER_H
#define MAKE_TRANSFER_FUNCTION_TEXTURE_UPDATER_H

#include <transferfunction/TransferFunctionTextureUpdater.h>

class Storage;

namespace Factory
{
    /**
    * Creates and initializes the transfer function texture updater.
    *
    * Constructs a TransferFunctionTextureUpdater that monitors GuiUpdateFlags for
    * changes to transfer function control points and regenerates the 1D transfer
    * function texture when needed. The updater performs Catmull-Rom spline
    * interpolation between control points and updates the texture data used for
    * volume rendering.
    *
    * @param storage Storage containing GUI update flags, transfer function, and textures.
    * @return Initialized TransferFunctionTextureUpdater object.
    *
    * @see TransferFunctionTextureUpdater for texture update implementation.
    * @see GuiUpdateFlags for parameter change tracking.
    * @see TransferFunction for control point management.
    * @see InterpolateTransferFunction for interpolation.
    */
    TransferFunctionTextureUpdater MakeTransferFunctionTextureUpdater(Storage& storage);
}

#endif
