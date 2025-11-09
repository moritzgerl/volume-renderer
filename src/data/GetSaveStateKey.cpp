#include <data/GetSaveStateKey.h>
#include <algorithm>
#include <array>

namespace
{
    struct SaveStateKeyMapping
    {
        std::string_view key;
        Data::SaveStateKey value;
    };

    constexpr std::array<SaveStateKeyMapping, 5> saveStateKeyLookup =
    {{
        {"Value", Data::SaveStateKey::Value},
        {"ColorR", Data::SaveStateKey::ColorR},
        {"ColorG", Data::SaveStateKey::ColorG},
        {"ColorB", Data::SaveStateKey::ColorB},
        {"Opacity", Data::SaveStateKey::Opacity}
    }};
}

Data::SaveStateKey Data::GetSaveStateKey(std::string_view key)
{
    auto it = std::find_if(saveStateKeyLookup.begin(), saveStateKeyLookup.end(),
        [key](const SaveStateKeyMapping& mapping)
        {
            return mapping.key == key;
        });

    return (it != saveStateKeyLookup.end()) ? it->value : SaveStateKey::Unknown;
}
