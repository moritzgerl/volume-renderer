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
    auto storage = Factory::MakeStorage();
    auto inputHandler = Factory::MakeInputHandler(storage);
    auto gui = Factory::MakeGui(storage);
    auto ssaoUpdater = Factory::MakeSsaoUpdater(storage);
    auto transferFunctionTextureUpdater = Factory::MakeTransferFunctionTextureUpdater(storage);
    const auto renderPasses = Factory::MakeRenderPasses(gui, inputHandler, storage);
    auto& window = storage.GetWindow();

    while (!window.ShouldClose())
    {
        inputHandler.Update();
        ssaoUpdater.Update();
        transferFunctionTextureUpdater.Update();

        for (const auto& renderPass : renderPasses)
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
