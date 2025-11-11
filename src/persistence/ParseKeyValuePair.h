#ifndef PARSE_KEY_VALUE_PAIR_H
#define PARSE_KEY_VALUE_PAIR_H

#include <persistence/KeyValuePair.h>
#include <string>

namespace Persistence
{   
    // TODO use std::expected    
    KeyValuePair ParseKeyValuePair(const std::string& line);
}

#endif
