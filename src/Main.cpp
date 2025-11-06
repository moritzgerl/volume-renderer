#include <context/GlfwWindow.h>
#include <gui/Gui.h>
#include <input/DisplayProperties.h>
#include <input/InputHandler.h>
#include <input/MakeInputHandler.h>
#include <renderpass/MakeRenderPasses.h>
#include <shader/SsaoUpdater.h>
#include <shader/MakeSsaoUpdater.h>
#include <storage/MakeStorage.h>
#include <storage/Storage.h>

#include <glad/glad.h>

int main()
{
    Storage storage(Factory::MakeStorage());
    InputHandler inputHandler = Factory::MakeInputHandler(storage);
    SsaoUpdater ssaoUpdater = Factory::MakeSsaoUpdater(storage);
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
