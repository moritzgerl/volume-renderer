#include <persistence/ParseElementIndex.h>
#include <persistence/ParseValue.h>
#include <persistence/ApplicationStateIniFileSection.h>

std::expected<unsigned int, Persistence::ApplicationStateIniFileLoadingError> Persistence::ParseElementIndex(const std::string_view line, Persistence::ApplicationStateIniFileSection currentSection)
{
    std::string_view elementIndexString;
    
    switch (currentSection)
    {
        case ApplicationStateIniFileSection::TransferFunctionPoint:
        {
            // TODO make robust
            elementIndexString = line.substr(22, line.size() - 23);
            break;
        }
        case ApplicationStateIniFileSection::PointLight:
        {
            // TODO make robust
            elementIndexString = line.substr(11, line.size() - 12);
            break;
        }
        default:
        {
            return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
        }
    }    
    
    auto parseValueResult = ParseValue<unsigned int>(elementIndexString);

    if (parseValueResult)
    {
        return parseValueResult.value();
    }
    else
    {
        return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
    }
}
