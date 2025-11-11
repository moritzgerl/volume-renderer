#include <persistence/ParseKeyValuePair.h>

Data::KeyValuePair Parsing::ParseKeyValuePair(const std::string& line)
{
    size_t equalPos = line.find('=');
    if (equalPos == std::string::npos)
    {
        return Data::KeyValuePair{ "", "" };
    }
    std::string key = line.substr(0, equalPos);
    std::string value = line.substr(equalPos + 1);

    key.erase(0, key.find_first_not_of(" \t"));
    key.erase(key.find_last_not_of(" \t") + 1);
    value.erase(0, value.find_first_not_of(" \t"));
    value.erase(value.find_last_not_of(" \t") + 1);

    return Data::KeyValuePair{ key, value };
}