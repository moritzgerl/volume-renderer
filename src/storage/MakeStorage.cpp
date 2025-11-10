#include <storage/MakeStorage.h>
#include <storage/ElementStorage.h>
#include <buffers/FrameBufferId.h>
#include <buffers/MakeFrameBuffers.h>
#include <camera/Camera.h>
#include <context/GlfwWindow.h>
#include <config/Config.h>
#include <data/LoadApplicationStateFromIniFile.h>
#include <data/LoadVolumeRaw.h>
#include <gui/GuiParameters.h>
#include <gui/GuiUpdateFlags.h>
#include <gui/MakeGuiParameters.h>
#include <gui/TransferFunction.h>
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

    bool IsTransferFunctionValid(const TransferFunction& transferFunction)
    {
        if (transferFunction.numActivePoints == 0)
        {
            return false;
        }

        if (transferFunction.numActivePoints > TransferFunction::maxControlPoints)
        {
            return false;
        }

        // TODO better
        for (size_t i = 0; i < transferFunction.numActivePoints; ++i)
        {
            const auto& point = transferFunction.controlPoints[i];
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

    Data::ApplicationState LoadApplicationState(const std::filesystem::path& applicationStateIniFilePath)
    {
        auto applicationStateResult = Data::LoadApplicationStateFromIniFile(applicationStateIniFilePath);
        if (!applicationStateResult)
        {
            return Data::ApplicationState{ .guiParameters = Factory::MakeGuiParameters() };
        }

        Data::ApplicationState applicationState = std::move(applicationStateResult).value();

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
        Context::GlfwWindow window;
        Data::ApplicationState applicationState = LoadApplicationState(Config::applicationStateIniFilePath);
        Camera camera(Config::defaultCameraPosition, Config::defaultCameraLookAt, Config::defaultCameraUp);
        DisplayProperties displayProperties = MakeDisplayProperties();
        GuiParameters guiParameters = std::move(applicationState.guiParameters);
        Data::VolumeData volumeData = LoadVolume(Config::datasetPath);
        GuiUpdateFlags guiUpdateFlags;
        ScreenQuad screenQuad;
        UnitCube unitCube;
        SsaoUtils ssaoUtils;
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
