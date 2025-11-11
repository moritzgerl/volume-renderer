#include <persistence/ParseValue.h>

#include <charconv>

template<typename T>
Persistence::ParseValueResult<T> Persistence::ParseValue(const std::string_view string)
{
    // TODO check if this is the best way 
    T out;    
    auto [ptr, errorCode] = std::from_chars(string.data(), string.data() + string.size(), out);

    if (errorCode == std::errc{})
    {
        return out;
    }
    else
    {
        return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
    }
}

template
Persistence::ParseValueResult<unsigned int> Persistence::ParseValue<unsigned int>(const std::string_view string);

template
Persistence::ParseValueResult<float> Persistence::ParseValue<float>(const std::string_view string);
