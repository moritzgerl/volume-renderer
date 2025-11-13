#ifndef MAKE_SSAO_UPDATER_H
#define MAKE_SSAO_UPDATER_H

#include <ssao/SsaoUpdater.h>

class Storage;

namespace Factory
{
    SsaoUpdater MakeSsaoUpdater(Storage& storage);
}

#endif
