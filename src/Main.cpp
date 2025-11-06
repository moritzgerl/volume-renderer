#include <context/GlfwWindow.h>
#include <gui/Gui.h>
#include <input/DisplayProperties.h>
#include <input/InputHandler.h>
#include <renderpass/MakeRenderPasses.h>
#include <shader/SsaoUpdater.h>
#include <storage/MakeStorage.h>
#include <storage/Storage.h>

#include <glad/glad.h>

int main()
{
    Storage storage(Factory::MakeStorage());
    Gui& gui = storage.GetGui();
    InputHandler& inputHandler = storage.GetInputHandler();
    SsaoUpdater& ssaoUpdater = storage.GetSsaoUpdater();
    Context::GlfwWindow& window = storage.GetWindow();
    const DisplayProperties& displayProperties = storage.GetDisplayProperties();
    const RenderPasses renderPasses = Factory::MakeRenderPasses(storage);

    while (!window.ShouldClose())
    {
        inputHandler.Update();
        ssaoUpdater.Update();

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
