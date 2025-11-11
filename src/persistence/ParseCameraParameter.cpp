#include <persistence/ParseCameraParameter.h>
#include <persistence/ParseValue.h>

bool Persistence::ParseCameraParameter(
    ApplicationStateIniFileKey key,
    std::string_view valueString,
    CameraParameters& cameraParameters)
{
    auto parseValueResult = ParseValue<float>(valueString);

    if (parseValueResult)
    {
        const float& value = parseValueResult.value();
        using Key = ApplicationStateIniFileKey;

        switch (key)
        {
        case Key::PositionX:
            cameraParameters.position.x = value;
            break;
        case Key::PositionY:
            cameraParameters.position.y = value;
            break;
        case Key::PositionZ:
            cameraParameters.position.z = value;
            break;
        case Key::Zoom:
            cameraParameters.zoom = value;
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
