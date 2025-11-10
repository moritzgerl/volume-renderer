#include <data/ParseElementIndex.h>
#include <data/ParseValue.h>
#include <data/ApplicationStateIniFileSection.h>

std::expected<unsigned int, Data::ApplicationStateIniFileLoadingError> Parsing::ParseElementIndex(const std::string_view line, Data::ApplicationStateIniFileSection currentSection)
{
    std::string_view elementIndexString;
    
    switch (currentSection)
    {
        case Data::ApplicationStateIniFileSection::TransferFunctionPoint:
        {
            elementIndexString = line.substr(22, line.size() - 23);
            break;
        }
        case Data::ApplicationStateIniFileSection::PointLight:
        {
            elementIndexString = line.substr(11, line.size() - 12);
            break;
        }
        default:
        {
            return std::unexpected(Data::ApplicationStateIniFileLoadingError::ParseError);
        }
    }    
    
    auto parseValueResult = Parsing::ParseValue<unsigned int>(elementIndexString);

    if (parseValueResult)
    {
        return parseValueResult.value();
    }
    else
    {
        return std::unexpected(Data::ApplicationStateIniFileLoadingError::ParseError);
    }
}