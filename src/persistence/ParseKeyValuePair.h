#ifndef PARSE_KEY_VALUE_PAIR_H
#define PARSE_KEY_VALUE_PAIR_H

#include <persistence/KeyValuePair.h>
#include <string>

namespace Parsing
{   
    // TODO use std::expected    
    Data::KeyValuePair ParseKeyValuePair(const std::string& line);
}

#endif
