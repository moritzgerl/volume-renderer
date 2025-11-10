#ifndef SAVE_STATE_KEY_H
#define SAVE_STATE_KEY_H

namespace Data
{
    /// Keys for save state file parsing
    enum class SaveStateKey
    {
        Value,
        ColorR,
        ColorG,
        ColorB,
        Opacity,
        Unknown
    };
}

#endif
