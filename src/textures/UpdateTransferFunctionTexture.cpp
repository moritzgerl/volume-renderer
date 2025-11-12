#include <textures/UpdateTransferFunctionTexture.h>
#include <textures/Texture.h>
#include <textures/TextureId.h>
#include <config/TransferFunctionConstants.h>
#include <gui/TransferFunction.h>

#include <glad/glad.h>

void TextureUtils::UpdateTransferFunctionTexture(const TransferFunction& transferFunction, Texture& transferFunctionTexture)
{
    transferFunctionTexture = Texture(
        TextureId::TransferFunction,
        transferFunctionTexture.GetTextureUnitEnum(),
        static_cast<unsigned int>(TransferFunctionConstants::textureSize),
        GL_RGBA,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        GL_LINEAR,
        GL_CLAMP_TO_EDGE,
        transferFunction.GetTextureData().data()
    );
}
