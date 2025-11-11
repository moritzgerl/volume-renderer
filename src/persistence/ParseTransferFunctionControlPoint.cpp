#include <persistence/ParseTransferFunctionControlPoint.h>
#include <persistence/ParseValue.h>

bool Persistence::ParseTransferFunctionControlPoint(
    ApplicationStateIniFileKey key,    
    std::string_view valueString,
    TransferFunctionControlPoint& point)
{
    auto parseValueResult = ParseValue<float>(valueString);

    if (parseValueResult)
    {
        const float& value = parseValueResult.value();
        using Key = ApplicationStateIniFileKey;

        switch (key)
        {
        case Key::Value:
            point.value = value;
            break;
        case Key::ColorR:
            point.color.r = value;
            break;
        case Key::ColorG:
            point.color.g = value;
            break;
        case Key::ColorB:
            point.color.b = value;
            break;
        case Key::Opacity:
            point.opacity = value;
            break;
        default:
            break;
        }

        return true;
    }
    else
    {
        return false;
    }
}
