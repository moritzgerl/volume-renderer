#ifndef MAKE_TRANSFER_FUNCTION_TEXTURE_UPDATER_H
#define MAKE_TRANSFER_FUNCTION_TEXTURE_UPDATER_H

#include <shader/TransferFunctionTextureUpdater.h>

class Storage;

namespace Factory
{
    TransferFunctionTextureUpdater MakeTransferFunctionTextureUpdater(Storage& storage);
}

#endif
