#include <gtest/gtest.h>

#include <context/GlfwWindow.h>
#include <context/InitGl.h>
#include <gui/GuiUpdateFlags.h>
#include <textures/Texture.h>
#include <textures/TextureId.h>
#include <transferfunction/TransferFunction.h>
#include <transferfunction/TransferFunctionTextureUpdater.h>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <memory>

class TransferFunctionTextureUpdaterTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        window = std::make_unique<Context::GlfwWindow>();
        Context::InitGl();

        transferFunction = std::make_unique<TransferFunction>();
        transferFunction->AddPoint(0.0f, 0.0f);
        transferFunction->AddPoint(1.0f, 1.0f);

        guiUpdateFlags = std::make_unique<GuiUpdateFlags>();

        // Create a 1D texture for transfer function
        texture = std::make_unique<Texture>(
            TextureId::TransferFunction,
            GL_TEXTURE0,
            256,
            GL_RGBA,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            GL_LINEAR,
            GL_CLAMP_TO_EDGE,
            nullptr
        );
    }

    std::unique_ptr<Context::GlfwWindow> window;
    std::unique_ptr<TransferFunction> transferFunction;
    std::unique_ptr<GuiUpdateFlags> guiUpdateFlags;
    std::unique_ptr<Texture> texture;
};

TEST_F(TransferFunctionTextureUpdaterTest, CanCreateUpdater)
{
    EXPECT_NO_THROW(TransferFunctionTextureUpdater(
        *guiUpdateFlags,
        *transferFunction,
        *texture
    ));
}

TEST_F(TransferFunctionTextureUpdaterTest, ConstructorUpdatesTexture)
{
    // Constructor should update texture immediately
    TransferFunctionTextureUpdater updater{
        *guiUpdateFlags,
        *transferFunction,
        *texture
    };

    // If texture was updated, GetGlId should return non-zero
    EXPECT_NE(texture->GetGlId(), 0u);
}

TEST_F(TransferFunctionTextureUpdaterTest, UpdateDoesNothingWhenFlagNotSet)
{
    TransferFunctionTextureUpdater updater{
        *guiUpdateFlags,
        *transferFunction,
        *texture
    };

    guiUpdateFlags->transferFunctionChanged = false;

    // Calling Update should not throw
    EXPECT_NO_THROW(updater.Update());
}

TEST_F(TransferFunctionTextureUpdaterTest, UpdateRegeneratesTextureWhenFlagSet)
{
    TransferFunctionTextureUpdater updater{
        *guiUpdateFlags,
        *transferFunction,
        *texture
    };

    guiUpdateFlags->transferFunctionChanged = true;

    EXPECT_NO_THROW(updater.Update());
}

TEST_F(TransferFunctionTextureUpdaterTest, UpdateClearsFlagAfterProcessing)
{
    TransferFunctionTextureUpdater updater{
        *guiUpdateFlags,
        *transferFunction,
        *texture
    };

    guiUpdateFlags->transferFunctionChanged = true;
    updater.Update();

    EXPECT_FALSE(guiUpdateFlags->transferFunctionChanged);
}

TEST_F(TransferFunctionTextureUpdaterTest, CanUpdateMultipleTimes)
{
    TransferFunctionTextureUpdater updater{
        *guiUpdateFlags,
        *transferFunction,
        *texture
    };

    for (int i = 0; i < 5; ++i)
    {
        guiUpdateFlags->transferFunctionChanged = true;
        EXPECT_NO_THROW(updater.Update());
        EXPECT_FALSE(guiUpdateFlags->transferFunctionChanged);
    }
}

TEST_F(TransferFunctionTextureUpdaterTest, UpdateHandlesEmptyTransferFunction)
{
    auto emptyTransferFunction = std::make_unique<TransferFunction>();
    // Don't add any points

    TransferFunctionTextureUpdater updater{
        *guiUpdateFlags,
        *emptyTransferFunction,
        *texture
    };

    guiUpdateFlags->transferFunctionChanged = true;

    EXPECT_NO_THROW(updater.Update());
}

TEST_F(TransferFunctionTextureUpdaterTest, UpdateHandlesSingleControlPoint)
{
    auto singlePointTf = std::make_unique<TransferFunction>();
    singlePointTf->AddPoint(0.5f, 0.5f);

    TransferFunctionTextureUpdater updater{
        *guiUpdateFlags,
        *singlePointTf,
        *texture
    };

    guiUpdateFlags->transferFunctionChanged = true;

    EXPECT_NO_THROW(updater.Update());
}

TEST_F(TransferFunctionTextureUpdaterTest, UpdateHandlesMultipleControlPoints)
{
    auto multiPointTf = std::make_unique<TransferFunction>();
    multiPointTf->AddPoint(0.0f, 0.0f);
    multiPointTf->AddPoint(0.25f, 0.3f);
    multiPointTf->AddPoint(0.5f, 0.6f);
    multiPointTf->AddPoint(0.75f, 0.9f);
    multiPointTf->AddPoint(1.0f, 1.0f);

    TransferFunctionTextureUpdater updater{
        *guiUpdateFlags,
        *multiPointTf,
        *texture
    };

    guiUpdateFlags->transferFunctionChanged = true;

    EXPECT_NO_THROW(updater.Update());
}

TEST_F(TransferFunctionTextureUpdaterTest, UpdateDoesNotCauseGLError)
{
    TransferFunctionTextureUpdater updater{
        *guiUpdateFlags,
        *transferFunction,
        *texture
    };

    guiUpdateFlags->transferFunctionChanged = true;
    updater.Update();

    EXPECT_EQ(glGetError(), GL_NO_ERROR);
}
