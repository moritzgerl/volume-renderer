#include <context/GlfwWindow.h>
#include <gui/Gui.h>
#include <input/DisplayProperties.h>
#include <input/InputHandler.h>
#include <renderpass/RenderPass.h>
#include <shader/SsaoUpdater.h>
#include <storage/MakeStorage.h>
#include <storage/Storage.h>

#include <glad/glad.h>

#include <vector>

int main()
{
    Storage storage(Factory::MakeStorage());
    const DisplayProperties& displayProperties = storage.GetDisplayProperties();
    Gui& gui = storage.GetGui();
    InputHandler& inputHandler = storage.GetInputHandler();
    SsaoUpdater& ssaoUpdater = storage.GetSsaoUpdater();
    const std::vector<RenderPass>& renderPasses = storage.GetRenderPasses();
    Context::GlfwWindow& window = storage.GetWindow();

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

    window.Shutdown();

    return 0;
}
