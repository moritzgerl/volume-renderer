#ifndef TRANSFER_FUNCTION_TEXTURE_UPDATER_H
#define TRANSFER_FUNCTION_TEXTURE_UPDATER_H

#include <config/TransferFunctionConstants.h>

#include <array>

struct GuiUpdateFlags;
class TransferFunction;
class Texture;

class TransferFunctionTextureUpdater
{
public:
    TransferFunctionTextureUpdater(
        GuiUpdateFlags& guiUpdateFlags,
        TransferFunction& transferFunction,
        Texture& transferFunctionTexture
    );

    void Update();

private:
    void UpdateTextureData();
    void UpdateTexture();

private:
    std::array<unsigned char, TransferFunctionConstants::textureDataSize> m_textureData;
    GuiUpdateFlags& m_guiUpdateFlags;
    TransferFunction& m_transferFunction;
    Texture& m_transferFunctionTexture;
};

#endif
