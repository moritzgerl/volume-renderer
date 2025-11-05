#include <storage/MakeStorage.h>
#include <storage/ElementStorage.h>
#include <buffers/FrameBufferId.h>
#include <buffers/MakeFrameBuffers.h>
#include <camera/Camera.h>
#include <context/GlfwWindow.h>
#include <gui/Gui.h>
#include <gui/GuiParameters.h>
#include <gui/GuiUpdateFlags.h>
#include <gui/MakeGuiParameters.h>
#include <input/DisplayProperties.h>
#include <input/InputHandler.h>
#include <input/MakeDisplayProperties.h>
#include <primitives/ScreenQuad.h>
#include <renderpass/MakeRenderPasses.h>
#include <shader/MakeShaders.h>
#include <shader/ShaderId.h>
#include <shader/SsaoUpdater.h>
#include <textures/MakeTextures.h>
#include <textures/TextureId.h>
#include <utils/SsaoUtils.h>

namespace Factory
{
    Storage MakeStorage()
    {
        Context::GlfwWindow window;
        Camera camera(-2.25293994f, 9.60278416f, -4.95751047f, 0.00000000f, 1.00000000f, 0.00000000f, 389.10012817f, -30.39993668f);
        DisplayProperties displayProperties = MakeDisplayProperties();
        GuiParameters guiParameters = MakeGuiParameters();
        GuiUpdateFlags guiUpdateFlags;
        Gui gui(window.GetWindow(), guiParameters, guiUpdateFlags);
        InputHandler inputHandler(window.GetWindow(), camera, displayProperties);
        ScreenQuad screenQuad;
        SsaoUtils ssaoUtils;
        TextureStorage textureStorage(MakeTextures(ssaoUtils));
        ShaderStorage shaderStorage(MakeShaders(guiParameters, ssaoUtils, textureStorage));
        FrameBufferStorage frameBufferStorage(MakeFrameBuffers(textureStorage));
        RenderPassStorage renderPassStorage(MakeRenderPasses(camera, displayProperties, guiParameters, inputHandler, ssaoUtils, screenQuad, textureStorage, shaderStorage, frameBufferStorage));
        
        Texture& ssaoNoiseTexture = textureStorage.GetElement(TextureId::SsaoNoise);
        const Shader& ssaoShader = shaderStorage.GetElement(ShaderId::Ssao);
        const Shader& ssaoFinalShader = shaderStorage.GetElement(ShaderId::SsaoFinal);        
        SsaoUpdater ssaoUpdater(guiUpdateFlags, guiParameters, ssaoUtils, ssaoNoiseTexture, ssaoShader, ssaoFinalShader);

        return Storage(
            std::move(camera),
            std::move(displayProperties),
            std::move(gui),
            std::move(guiParameters),
            std::move(guiUpdateFlags),
            std::move(inputHandler),
            std::move(screenQuad),
            std::move(ssaoUpdater),
            std::move(ssaoUtils),
            std::move(textureStorage),
            std::move(shaderStorage),
            std::move(frameBufferStorage),
            std::move(renderPassStorage),
            std::move(window)
        );
    }
}
