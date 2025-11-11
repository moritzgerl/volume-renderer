#ifndef KEY_VALUE_PAIR_H
#define KEY_VALUE_PAIR_H

#include <string_view>

namespace Persistence
{
    struct KeyValuePair
    {
        std::string_view key;
        std::string_view value;
    };
}

#endif
