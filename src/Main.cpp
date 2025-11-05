#include <buffers/FrameBuffer.h>
#include <buffers/FrameBufferId.h>
#include <config/Config.h>
#include <context/GlfwWindow.h>
#include <camera/Camera.h>
#include <input/MakeDisplayProperties.h>
#include <input/DisplayProperties.h>
#include <input/InputHandler.h>
#include <gui/Gui.h>
#include <gui/GuiParameters.h>
#include <gui/GuiUpdateFlags.h>
#include <gui/MakeGuiParameters.h>
#include <primitives/ScreenQuad.h>
#include <shader/Shader.h>
#include <shader/ShaderId.h>
#include <shader/UpdateLightingParametersInShader.h>
#include <storage/Storage.h>
#include <storage/MakeStorage.h>
#include <shader/UpdateCameraMatricesInShader.h>
#include <shader/UpdateLightSourceModelMatrixInShader.h>
#include <shader/UpdateSsaoFinalShader.h>
#include <shader/UpdateSsaoShader.h>
#include <shader/SsaoUpdater.h>
#include <textures/Texture.h>
#include <textures/TextureId.h>
#include <textures/UpdateSsaoNoiseTexture.h>
#include <utils/SsaoUtils.h>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <numbers>
#include <iostream>

int main()
{
    Context::GlfwWindow window;

    DisplayProperties displayProperties = Factory::MakeDisplayProperties();
    GuiParameters guiParameters = Factory::MakeGuiParameters();
    GuiUpdateFlags guiUpdateFlags;
    Gui gui(window.GetWindow(), guiParameters, guiUpdateFlags);
    SsaoUtils ssaoUtils;
    Camera camera(-2.25293994f, 9.60278416f, -4.95751047f, 0.00000000f, 1.00000000f, 0.00000000f, 389.10012817f, -30.39993668f);
    InputHandler inputHandler(window.GetWindow(), camera, displayProperties);
    ScreenQuad screenQuad;
    Storage storage(Factory::MakeStorage(camera, displayProperties, guiParameters, ssaoUtils, screenQuad));
    Texture& ssaoNoiseTexture = storage.GetTexture(TextureId::SsaoNoise);
    const Shader& ssaoShader = storage.GetShader(ShaderId::Ssao);
    const Shader& ssaoFinalShader = storage.GetShader(ShaderId::SsaoFinal);
    const FrameBuffer& ssaoInputFrameBuffer = storage.GetFrameBuffer(FrameBufferId::SsaoInput);
    const std::vector<RenderPass>& renderPasses = storage.GetRenderPasses();
    SsaoUpdater ssaoUpdater(guiUpdateFlags, guiParameters, ssaoUtils, ssaoNoiseTexture, ssaoShader, ssaoFinalShader);

    while (!window.ShouldClose())
    {
        inputHandler.Update();
        ssaoUpdater.Update();

        glViewport(0, 0, inputHandler.GetWindowWidth(), inputHandler.GetWindowHeight());
        glDisable(GL_BLEND);

        for (const RenderPass& renderPass : renderPasses)
        {
            renderPass.Render();
        }

        if (displayProperties.showGui)
        {
            gui.Draw();
        }

        window.PostRender();
    }

    gui.Shutdown();
    window.Shutdown();

    return 0;
}
