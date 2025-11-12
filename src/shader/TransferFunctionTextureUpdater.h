#ifndef TRANSFER_FUNCTION_TEXTURE_UPDATER_H
#define TRANSFER_FUNCTION_TEXTURE_UPDATER_H

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
    GuiUpdateFlags& m_guiUpdateFlags;
    TransferFunction& m_transferFunction;
    Texture& m_transferFunctionTexture;
};

#endif
