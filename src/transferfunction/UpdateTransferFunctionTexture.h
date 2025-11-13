#ifndef UPDATE_TRANSFER_FUNCTION_TEXTURE_H
#define UPDATE_TRANSFER_FUNCTION_TEXTURE_H

class TransferFunction;
class Texture;

namespace TextureUtils
{
    void UpdateTransferFunctionTexture(const TransferFunction& transferFunction, Texture& transferFunctionTexture);
}

#endif
