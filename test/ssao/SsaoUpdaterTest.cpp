#include <gtest/gtest.h>

#include <context/GlfwWindow.h>
#include <context/InitGl.h>
#include <gui/GuiParameters.h>
#include <gui/GuiUpdateFlags.h>
#include <gui/MakeDefaultGuiParameters.h>
#include <shader/Shader.h>
#include <ssao/SsaoKernel.h>
#include <ssao/SsaoUpdater.h>
#include <textures/Texture.h>
#include <textures/TextureId.h>
#include <utils/FileSystem.h>

#include <glad/glad.h>
#include <memory>

class SsaoUpdaterTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        window = std::make_unique<Context::GlfwWindow>();
        Context::InitGl();

        guiParameters = Factory::MakeDefaultGuiParameters();
        guiUpdateFlags = GuiUpdateFlags{};
        ssaoKernel = std::make_unique<SsaoKernel>();

        ssaoNoiseTexture = std::make_unique<Texture>(
            TextureId::SsaoNoise,
            1,
            4,
            4,
            GL_RGBA32F,
            GL_RGB,
            GL_FLOAT,
            GL_NEAREST,
            GL_REPEAT
        );

        ssaoShader = std::make_unique<Shader>(ShaderId::Ssao, FileSystem::GetPath("src/shaders/Ssao.vert").string().c_str(), FileSystem::GetPath("src/shaders/Ssao.frag").string().c_str());
        ssaoFinalShader = std::make_unique<Shader>(ShaderId::SsaoFinal, FileSystem::GetPath("src/shaders/SsaoFinal.vert").string().c_str(), FileSystem::GetPath("src/shaders/SsaoFinal.frag").string().c_str());
    }

    std::unique_ptr<Context::GlfwWindow> window;
    GuiParameters guiParameters;
    GuiUpdateFlags guiUpdateFlags;
    std::unique_ptr<SsaoKernel> ssaoKernel;
    std::unique_ptr<Texture> ssaoNoiseTexture;
    std::unique_ptr<Shader> ssaoShader;
    std::unique_ptr<Shader> ssaoFinalShader;
};

TEST_F(SsaoUpdaterTest, CanCreateSsaoUpdater)
{
    EXPECT_NO_THROW(SsaoUpdater updater(
        guiUpdateFlags,
        guiParameters,
        *ssaoKernel,
        *ssaoNoiseTexture,
        *ssaoShader,
        *ssaoFinalShader
    ));
}

TEST_F(SsaoUpdaterTest, UpdateDoesNothingWhenFlagIsFalse)
{
    guiUpdateFlags.ssaoParametersChanged = false;

    SsaoUpdater updater{
        guiUpdateFlags,
        guiParameters,
        *ssaoKernel,
        *ssaoNoiseTexture,
        *ssaoShader,
        *ssaoFinalShader
    };

    EXPECT_NO_THROW(updater.Update());
    EXPECT_FALSE(guiUpdateFlags.ssaoParametersChanged);
}

TEST_F(SsaoUpdaterTest, UpdateClearsFlagWhenParametersChanged)
{
    guiUpdateFlags.ssaoParametersChanged = true;

    SsaoUpdater updater{
        guiUpdateFlags,
        guiParameters,
        *ssaoKernel,
        *ssaoNoiseTexture,
        *ssaoShader,
        *ssaoFinalShader
    };

    updater.Update();
    EXPECT_FALSE(guiUpdateFlags.ssaoParametersChanged);
}

TEST_F(SsaoUpdaterTest, CanCallUpdateMultipleTimes)
{
    SsaoUpdater updater{
        guiUpdateFlags,
        guiParameters,
        *ssaoKernel,
        *ssaoNoiseTexture,
        *ssaoShader,
        *ssaoFinalShader
    };

    EXPECT_NO_THROW(updater.Update());
    EXPECT_NO_THROW(updater.Update());
    EXPECT_NO_THROW(updater.Update());
}

TEST_F(SsaoUpdaterTest, UpdateProcessesChangesWhenFlagIsSet)
{
    guiUpdateFlags.ssaoParametersChanged = true;
    guiParameters.ssaoKernelSize = 32;

    SsaoUpdater updater{
        guiUpdateFlags,
        guiParameters,
        *ssaoKernel,
        *ssaoNoiseTexture,
        *ssaoShader,
        *ssaoFinalShader
    };

    EXPECT_NO_THROW(updater.Update());
    EXPECT_FALSE(guiUpdateFlags.ssaoParametersChanged);
}

TEST_F(SsaoUpdaterTest, UpdateCanHandleMultipleChanges)
{
    SsaoUpdater updater{
        guiUpdateFlags,
        guiParameters,
        *ssaoKernel,
        *ssaoNoiseTexture,
        *ssaoShader,
        *ssaoFinalShader
    };

    guiUpdateFlags.ssaoParametersChanged = true;
    updater.Update();
    EXPECT_FALSE(guiUpdateFlags.ssaoParametersChanged);

    guiUpdateFlags.ssaoParametersChanged = true;
    guiParameters.ssaoKernelSize = 128;
    updater.Update();
    EXPECT_FALSE(guiUpdateFlags.ssaoParametersChanged);
}

TEST_F(SsaoUpdaterTest, UpdateDoesNotCauseGLError)
{
    guiUpdateFlags.ssaoParametersChanged = true;

    SsaoUpdater updater{
        guiUpdateFlags,
        guiParameters,
        *ssaoKernel,
        *ssaoNoiseTexture,
        *ssaoShader,
        *ssaoFinalShader
    };

    updater.Update();
    EXPECT_EQ(glGetError(), GL_NO_ERROR);
}
