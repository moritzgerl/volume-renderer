#include <persistence/ParseElementIndex.h>
#include <persistence/ApplicationStateIniFileSectionNames.h>
#include <persistence/ApplicationStateIniFileSection.h>
#include <persistence/ParseValue.h>

std::expected<unsigned int, Persistence::ApplicationStateIniFileLoadingError> Persistence::ParseElementIndex(const std::string_view line, Persistence::ApplicationStateIniFileSection currentSection)
{
    std::string_view prefix;

    switch (currentSection)
    {
        case ApplicationStateIniFileSection::TransferFunctionPoint:
            prefix = SectionNames::transferFunctionPointPrefix;
            break;
        case ApplicationStateIniFileSection::PointLight:
            prefix = SectionNames::pointLightPrefix;
            break;
        default:
            return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
    }

    if (line.size() <= prefix.size() + 1)
    {
        return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
    }

    size_t closingBracketPos = line.find(']', prefix.size());
    if (closingBracketPos == std::string_view::npos)
    {
        return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
    }

    std::string_view elementIndexString = line.substr(prefix.size(), closingBracketPos - prefix.size());

    if (elementIndexString.empty())
    {
        return std::unexpected(ApplicationStateIniFileLoadingError::ParseError);
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
