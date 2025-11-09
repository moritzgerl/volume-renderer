#include <data/StoreSaveStateToIni.h>

#include <fstream>
#include <iomanip>

std::expected<void, Data::SaveStateSavingError> Data::StoreSaveStateToIni(const std::filesystem::path& iniFilePath, const SaveState& saveState)
{
    std::ofstream file(iniFilePath);
    if (!file.is_open())
    {
        return std::unexpected(SaveStateSavingError::CannotOpenFile);
    }

    file << std::fixed << std::setprecision(6);

    file << "[SaveState]\n";
    file << "\n";

    // TODO nice
    for (size_t i = 0; i < saveState.transferFunction.numActivePoints; ++i)
    {
        const auto& point = saveState.transferFunction.controlPoints[i];

        file << "[Point" << i << "]\n";
        file << "Value=" << point.value << "\n";
        file << "ColorR=" << point.color.r << "\n";
        file << "ColorG=" << point.color.g << "\n";
        file << "ColorB=" << point.color.b << "\n";
        file << "Opacity=" << point.opacity << "\n";
        file << "\n";
    }

    if (!file.good())
    {
        return std::unexpected(SaveStateSavingError::WriteError);
    }

    return {};
}
