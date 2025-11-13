#include <context/GlfwWindow.h>
#include <gui/Gui.h>
#include <gui/MakeGui.h>
#include <input/DisplayProperties.h>
#include <input/InputHandler.h>
#include <input/MakeInputHandler.h>
#include <renderpass/MakeRenderPasses.h>
#include <ssao/SsaoUpdater.h>
#include <ssao/MakeSsaoUpdater.h>
#include <storage/MakeStorage.h>
#include <storage/Storage.h>
#include <transferfunction/TransferFunctionTextureUpdater.h>
#include <transferfunction/MakeTransferFunctionTextureUpdater.h>

#include <glad/glad.h>

int main()
{
    Storage storage(Factory::MakeStorage());
    InputHandler inputHandler = Factory::MakeInputHandler(storage);
    Gui gui = Factory::MakeGui(storage);
    SsaoUpdater ssaoUpdater = Factory::MakeSsaoUpdater(storage);
    TransferFunctionTextureUpdater transferFunctionTextureUpdater = Factory::MakeTransferFunctionTextureUpdater(storage);
    const RenderPasses renderPasses = Factory::MakeRenderPasses(gui, inputHandler, storage);
    Context::GlfwWindow& window = storage.GetWindow();

    while (!window.ShouldClose())
    {
        inputHandler.Update();
        ssaoUpdater.Update();
        transferFunctionTextureUpdater.Update();

        for (const RenderPass& renderPass : renderPasses)
        {
            renderPass.Render();
        }

        gui.Draw();
        window.PostRender();
    }

    storage.SaveApplicationState();
    window.Shutdown();

    return 0;
}
