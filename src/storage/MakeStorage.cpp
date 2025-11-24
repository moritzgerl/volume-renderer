#include <storage/MakeStorage.h>
#include <storage/ElementStorage.h>

#include <buffers/FrameBufferId.h>
#include <buffers/MakeFrameBuffers.h>
#include <camera/Camera.h>
#include <config/Config.h>
#include <context/GlfwWindow.h>
#include <gui/GuiParameters.h>
#include <gui/GuiUpdateFlags.h>
#include <input/DisplayProperties.h>
#include <input/InputHandler.h>
#include <input/MakeDisplayProperties.h>
#include <persistence/LoadApplicationStateFromIniFile.h>
#include <persistence/MakeDefaultApplicationState.h>
#include <primitives/ScreenQuad.h>
#include <primitives/UnitCube.h>
#include <renderpass/MakeRenderPasses.h>
#include <shader/MakeShaders.h>
#include <shader/ShaderId.h>
#include <ssao/SsaoKernel.h>
#include <ssao/SsaoUpdater.h>
#include <textures/MakeTextures.h>
#include <textures/TextureId.h>
#include <transferfunction/TransferFunction.h>
#include <volumedata/LoadVolumeRaw.h>

#include <cstdlib>
#include <iostream>

namespace
{
    VolumeData::VolumeData LoadVolume(const std::filesystem::path& datasetPath)
    {
        auto volumeLoadingResult = VolumeData::LoadVolumeRaw(datasetPath);
        if (!volumeLoadingResult)
        {
            std::cerr << "Failed to load volume from " << datasetPath << std::endl;
            std::exit(EXIT_FAILURE);
        }
        return std::move(volumeLoadingResult).value();
    }

    bool IsTransferFunctionValid(const TransferFunction& transferFunction)
    {
        if (transferFunction.GetNumActivePoints() == 0)
        {
            return false;
        }

        if (transferFunction.GetNumActivePoints() > TransferFunctionConstants::maxNumControlPoints)
        {
            return false;
        }

        // TODO better
        for (auto i = size_t{0}; i < transferFunction.GetNumActivePoints(); ++i)
        {
            const auto& point = transferFunction[i];
            if (point.value < 0.0f || point.value > 1.0f ||
                point.opacity < 0.0f || point.opacity > 1.0f ||
                point.color.r < 0.0f || point.color.r > 1.0f ||
                point.color.g < 0.0f || point.color.g > 1.0f ||
                point.color.b < 0.0f || point.color.b > 1.0f)
            {
                return false;
            }
        }

        return true;
    }

    Persistence::ApplicationState LoadApplicationState(const std::filesystem::path& applicationStateIniFilePath)
    {
        auto applicationStateResult = Persistence::LoadApplicationStateFromIniFile(applicationStateIniFilePath);

        if (!applicationStateResult)
        {
            return Factory::MakeDefaultApplicationState();
        }

        auto applicationState = std::move(applicationStateResult).value();

        if (!IsTransferFunctionValid(applicationState.guiParameters.transferFunction))
        {
            applicationState.guiParameters.transferFunction = Config::defaultTransferFunction;
        }

        return applicationState;
    }
} // anonymous namespace

namespace Factory
{
    Storage MakeStorage()
    {
        auto window = Context::GlfwWindow{};
        auto applicationState = LoadApplicationState(Config::applicationStateIniFilePath);
        auto camera = Camera{applicationState.cameraParameters};
        auto guiParameters = std::move(applicationState.guiParameters);
        auto displayProperties = MakeDisplayProperties();
        auto volumeData = LoadVolume(Config::datasetPath);
        auto guiUpdateFlags = GuiUpdateFlags{};
        auto screenQuad = ScreenQuad{};
        auto unitCube = UnitCube{};
        auto ssaoKernel = SsaoKernel{};
        auto textureStorage = TextureStorage{MakeTextures(volumeData, ssaoKernel)};
        auto shaderStorage = ShaderStorage{MakeShaders(guiParameters, ssaoKernel, textureStorage)};
        auto frameBufferStorage = FrameBufferStorage{MakeFrameBuffers(textureStorage)};

        return Storage(
            std::move(camera),
            std::move(displayProperties),
            std::move(guiParameters),
            std::move(guiUpdateFlags),
            std::move(screenQuad),
            std::move(ssaoKernel),
            std::move(textureStorage),
            std::move(shaderStorage),
            std::move(frameBufferStorage),
            std::move(unitCube),
            std::move(volumeData),
            std::move(window)
        );
    }
}
