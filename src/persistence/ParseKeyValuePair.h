#ifndef PARSE_KEY_VALUE_PAIR_H
#define PARSE_KEY_VALUE_PAIR_H

#include <persistence/KeyValuePair.h>

#include <string_view>

namespace Persistence
{
    KeyValuePair ParseKeyValuePair(std::string_view line);
}

#endif
