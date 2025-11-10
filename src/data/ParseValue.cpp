#include <data/ParseValue.h>

#include <charconv>

template<typename T>
Parsing::ParseValueResult<T> Parsing::ParseValue(const std::string_view string)
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
        return std::unexpected(Data::ApplicationStateIniFileLoadingError::ParseError);
    }
}

template
Parsing::ParseValueResult<unsigned int> Parsing::ParseValue<unsigned int>(const std::string_view string);

template
Parsing::ParseValueResult<float> Parsing::ParseValue<float>(const std::string_view string);