/**
* \file TransferFunctionTextureUpdater.h
*
* \brief Monitors and updates the transfer function 1D texture when control points change.
*/

#ifndef TRANSFER_FUNCTION_TEXTURE_UPDATER_H
#define TRANSFER_FUNCTION_TEXTURE_UPDATER_H

#include <config/TransferFunctionConstants.h>

#include <array>

struct GuiUpdateFlags;
class TransferFunction;
class Texture;

/**
* \class TransferFunctionTextureUpdater
*
* \brief Updates the transfer function texture when control points are modified.
*
* Monitors GuiUpdateFlags to detect when the transfer function control points
* have been edited via the GUI. When changes are detected, interpolates the
* control points into a continuous 1D texture and uploads it to the GPU.
*
* The updater owns a buffer for the interpolated texture data and updates the
* texture in Storage via reference. The update flag is cleared after processing.
*
* @see TransferFunction for control point storage and manipulation.
* @see InterpolateTransferFunction for generating texture data from control points.
* @see GuiUpdateFlags for change detection.
* @see Texture for OpenGL texture management.
*/
class TransferFunctionTextureUpdater
{
public:
    /**
    * Constructor.
    * @param guiUpdateFlags Reference to GUI update flags for change detection.
    * @param transferFunction Reference to the transfer function with control points.
    * @param transferFunctionTexture Reference to the 1D texture to update.
    */
    TransferFunctionTextureUpdater(
        GuiUpdateFlags& guiUpdateFlags,
        TransferFunction& transferFunction,
        Texture& transferFunctionTexture
    );

    /**
    * Checks for transfer function changes and updates the texture if needed.
    * Should be called once per frame before rendering.
    * @return void
    */
    void Update();

private:
    /**
    * Interpolates control points into continuous texture data.
    */
    void UpdateTextureData();

    /**
    * Uploads the interpolated texture data to the GPU.
    */
    void UpdateTexture();

private:
    std::array<unsigned char, TransferFunctionConstants::textureDataSize> m_textureData; /**< Buffer for interpolated RGBA texture data. */
    GuiUpdateFlags& m_guiUpdateFlags; /**< Reference to GUI update flags. */
    TransferFunction& m_transferFunction; /**< Reference to transfer function with control points. */
    Texture& m_transferFunctionTexture; /**< Reference to 1D texture to update. */
};

#endif
