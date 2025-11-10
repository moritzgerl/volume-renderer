#ifndef GET_SAVE_STATE_KEY_H
#define GET_SAVE_STATE_KEY_H

#include <data/SaveStateKey.h>
#include <string_view>

namespace Data
{
    SaveStateKey GetSaveStateKey(std::string_view key);
}

#endif
