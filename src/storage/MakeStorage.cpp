#include <storage/MakeStorage.h>
#include <storage/ElementStorage.h>
#include <buffers/FrameBufferId.h>
#include <buffers/MakeFrameBuffers.h>
#include <camera/Camera.h>
#include <context/GlfwWindow.h>
#include <config/Config.h>
#include <data/LoadSaveStateFromIni.h>
#include <data/LoadVolumeRaw.h>
#include <gui/GuiParameters.h>
#include <gui/GuiUpdateFlags.h>
#include <gui/MakeGuiParameters.h>
#include <input/DisplayProperties.h>
#include <input/InputHandler.h>
#include <input/MakeDisplayProperties.h>
#include <primitives/ScreenQuad.h>
#include <primitives/UnitCube.h>
#include <renderpass/MakeRenderPasses.h>
#include <shader/MakeShaders.h>
#include <shader/ShaderId.h>
#include <shader/SsaoUpdater.h>
#include <textures/MakeTextures.h>
#include <textures/TextureId.h>
#include <utils/SsaoUtils.h>

#include <cstdlib>
#include <iostream>
#include <optional>

namespace
{
    Data::VolumeData LoadVolume(const std::filesystem::path& datasetPath)
    {
        auto volumeLoadingResult = Data::LoadVolumeRaw(datasetPath);
        if (!volumeLoadingResult)
        {
            std::cerr << "Failed to load volume from " << datasetPath << std::endl;
            std::exit(EXIT_FAILURE);
        }
        return std::move(volumeLoadingResult).value();
    }

    std::optional<Data::SaveState> LoadSaveState(const std::filesystem::path& saveStatePath)
    {
        auto saveStateResult = Data::LoadSaveStateFromIni(saveStatePath);
        if (!saveStateResult)
        {
            return std::nullopt;
        }
        return std::move(saveStateResult).value();
    }
} // anonymous namespace

namespace Factory
{
    Storage MakeStorage()
    {
        Context::GlfwWindow window;
        Camera camera(1.1f, 0.73f, 1.1f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
        DisplayProperties displayProperties = MakeDisplayProperties();
        std::optional<Data::SaveState> saveState = LoadSaveState(Config::saveStatePath);
        GuiParameters guiParameters = MakeGuiParameters(saveState);
        GuiUpdateFlags guiUpdateFlags;
        ScreenQuad screenQuad;
        UnitCube unitCube;
        SsaoUtils ssaoUtils;
        Data::VolumeData volumeData = LoadVolume(Config::datasetPath);
        TextureStorage textureStorage(MakeTextures(volumeData, ssaoUtils));
        ShaderStorage shaderStorage(MakeShaders(guiParameters, ssaoUtils, textureStorage));
        FrameBufferStorage frameBufferStorage(MakeFrameBuffers(textureStorage));

        return Storage(
            std::move(camera),
            std::move(displayProperties),
            std::move(guiParameters),
            std::move(guiUpdateFlags),
            std::move(screenQuad),
            std::move(ssaoUtils),
            std::move(textureStorage),
            std::move(shaderStorage),
            std::move(frameBufferStorage),
            std::move(unitCube),
            std::move(volumeData),
            std::move(window)
        );
    }
}
