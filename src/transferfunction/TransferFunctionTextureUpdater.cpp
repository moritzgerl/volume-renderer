#include <transferfunction/TransferFunctionTextureUpdater.h>
#include <config/TransferFunctionConstants.h>
#include <gui/GuiUpdateFlags.h>
#include <textures/Texture.h>
#include <textures/TextureId.h>
#include <transferfunction/TransferFunction.h>

#include <glad/glad.h>

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
        UpdateTransferFunctionTexture();
        m_guiUpdateFlags.transferFunctionChanged = false;
    }
}

void TransferFunctionTextureUpdater::UpdateTransferFunctionTexture()
{
    m_transferFunctionTexture = Texture(
        TextureId::TransferFunction,
        m_transferFunctionTexture.GetTextureUnitEnum(),
        static_cast<unsigned int>(TransferFunctionConstants::textureSize),
        GL_RGBA,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        GL_LINEAR,
        GL_CLAMP_TO_EDGE,
        m_transferFunction.GetTextureData().data()
    );
}
