#include <transferfunction/TransferFunctionTextureUpdater.h>

#include <gui/GuiUpdateFlags.h>
#include <textures/Texture.h>
#include <transferfunction/TransferFunction.h>
#include <transferfunction/UpdateTransferFunctionTexture.h>

TransferFunctionTextureUpdater::TransferFunctionTextureUpdater(
    GuiUpdateFlags& guiUpdateFlags,
    TransferFunction& transferFunction,
    Texture& transferFunctionTexture
)
    : m_guiUpdateFlags(guiUpdateFlags)
    , m_transferFunction(transferFunction)
    , m_transferFunctionTexture(transferFunctionTexture)
{
}

void TransferFunctionTextureUpdater::Update()
{
    if (m_guiUpdateFlags.transferFunctionChanged)
    {
        m_transferFunction.UpdateTextureData();
        TextureUtils::UpdateTransferFunctionTexture(m_transferFunction, m_transferFunctionTexture);
        m_guiUpdateFlags.transferFunctionChanged = false;
    }
}
