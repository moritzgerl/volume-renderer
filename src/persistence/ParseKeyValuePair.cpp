#include <persistence/ParseKeyValuePair.h>

namespace
{
    std::string_view TrimWhitespace(std::string_view str)
    {
        const size_t start = str.find_first_not_of(" \t");
        if (start == std::string_view::npos)
        {
            return std::string_view();
        }

        const size_t end = str.find_last_not_of(" \t");
        return str.substr(start, end - start + 1);
    }
}

std::expected<Persistence::KeyValuePair, Persistence::ApplicationStateIniFileLoadingError> Persistence::ParseKeyValuePair(std::string_view line)
{
    const size_t equalPos = line.find('=');
    if (equalPos == std::string_view::npos)
    {
        return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
    }

    std::string_view key = line.substr(0, equalPos);
    std::string_view value = line.substr(equalPos + 1);

    key = TrimWhitespace(key);
    value = TrimWhitespace(value);

    if (key.empty())
    {
        return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
    }

    return KeyValuePair{ key, value };
}
