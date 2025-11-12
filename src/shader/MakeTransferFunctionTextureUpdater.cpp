#include <shader/MakeTransferFunctionTextureUpdater.h>
#include <gui/GuiParameters.h>
#include <storage/Storage.h>
#include <textures/TextureId.h>

TransferFunctionTextureUpdater Factory::MakeTransferFunctionTextureUpdater(Storage& storage)
{
    return TransferFunctionTextureUpdater(
        storage.GetGuiUpdateFlags(),
        storage.GetGuiParameters().transferFunction,
        storage.GetTexture(TextureId::TransferFunction)
    );
}
