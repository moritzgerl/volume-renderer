#ifndef MAKE_STORAGE_H
#define MAKE_STORAGE_H

#include <storage/Storage.h>

class SsaoUtils;

namespace Factory
{
    Storage MakeStorage(const SsaoUtils& ssaoUtils);
}

#endif
