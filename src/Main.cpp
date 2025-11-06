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
    // TODO act factory functions, change back constructors to get only what they need
    InputHandler inputHandler(storage);
    SsaoUpdater ssaoUpdater(storage);
    const RenderPasses renderPasses = Factory::MakeRenderPasses(inputHandler, storage);
    const DisplayProperties& displayProperties = storage.GetDisplayProperties();
    Context::GlfwWindow& window = storage.GetWindow();
    Gui& gui = storage.GetGui();

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
