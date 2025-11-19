#include <gtest/gtest.h>

#include <context/GlfwWindow.h>
#include <context/InitGl.h>
#include <renderpass/RenderPass.h>
#include <shader/Shader.h>
#include <buffers/FrameBuffer.h>
#include <textures/Texture.h>

#include <glad/glad.h>
#include <memory>
#include <functional>

class RenderPassTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        window = std::make_unique<Context::GlfwWindow>();
        Context::InitGl();

        // Create a minimal shader for testing
        shader = std::make_unique<Shader>(
            ShaderId::Volume,
            "src/shaders/volume.vert",
            "src/shaders/volume.frag"
        );

        // Create a simple framebuffer
        frameBuffer = std::make_unique<FrameBuffer>(FrameBufferId::Default);

        // Create a simple 2D texture
        texture = std::make_unique<Texture>(
            TextureId::TransferFunction,
            0,
            256,
            256,
            GL_RGBA,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            GL_LINEAR,
            GL_CLAMP_TO_EDGE
        );

        prepareCallCount = 0;
        renderCallCount = 0;
    }

    std::unique_ptr<Context::GlfwWindow> window;
    std::unique_ptr<Shader> shader;
    std::unique_ptr<FrameBuffer> frameBuffer;
    std::unique_ptr<Texture> texture;

    int prepareCallCount;
    int renderCallCount;
};

TEST_F(RenderPassTest, CanCreateRenderPass)
{
    std::vector<std::reference_wrapper<const Texture>> textures;
    textures.push_back(std::cref(*texture));

    EXPECT_NO_THROW(RenderPass renderPass(RenderPassId::Volume, *shader, *frameBuffer, std::move(textures), []() {}, []() {}));
}

TEST_F(RenderPassTest, GetIdReturnsCorrectId)
{
    std::vector<std::reference_wrapper<const Texture>> textures;

    RenderPass renderPass{
        RenderPassId::Volume,
        *shader,
        *frameBuffer,
        std::move(textures),
        []() {},
        []() {}
    };

    EXPECT_EQ(renderPass.GetId(), RenderPassId::Volume);
}

TEST_F(RenderPassTest, GetIdReturnsCorrectIdForDifferentPassType)
{
    std::vector<std::reference_wrapper<const Texture>> textures;

    RenderPass renderPass{
        RenderPassId::Ssao,
        *shader,
        *frameBuffer,
        std::move(textures),
        []() {},
        []() {}
    };

    EXPECT_EQ(renderPass.GetId(), RenderPassId::Ssao);
}

TEST_F(RenderPassTest, RenderCallsPrepareFunctionOnce)
{
    std::vector<std::reference_wrapper<const Texture>> textures;

    RenderPass renderPass{
        RenderPassId::Volume,
        *shader,
        *frameBuffer,
        std::move(textures),
        [this]() { prepareCallCount++; },
        []() {}
    };

    renderPass.Render();
    EXPECT_EQ(prepareCallCount, 1);
}

TEST_F(RenderPassTest, RenderCallsRenderFunctionOnce)
{
    std::vector<std::reference_wrapper<const Texture>> textures;

    RenderPass renderPass{
        RenderPassId::Volume,
        *shader,
        *frameBuffer,
        std::move(textures),
        []() {},
        [this]() { renderCallCount++; }
    };

    renderPass.Render();
    EXPECT_EQ(renderCallCount, 1);
}

TEST_F(RenderPassTest, RenderCallsBothFunctionsInOrder)
{
    std::vector<std::reference_wrapper<const Texture>> textures;
    std::vector<int> callOrder;

    RenderPass renderPass{
        RenderPassId::Volume,
        *shader,
        *frameBuffer,
        std::move(textures),
        [&callOrder]() { callOrder.push_back(1); },
        [&callOrder]() { callOrder.push_back(2); }
    };

    renderPass.Render();

    ASSERT_EQ(callOrder.size(), 2u);
    EXPECT_EQ(callOrder[0], 1);
    EXPECT_EQ(callOrder[1], 2);
}

TEST_F(RenderPassTest, CanRenderMultipleTimes)
{
    std::vector<std::reference_wrapper<const Texture>> textures;

    RenderPass renderPass{
        RenderPassId::Volume,
        *shader,
        *frameBuffer,
        std::move(textures),
        [this]() { prepareCallCount++; },
        [this]() { renderCallCount++; }
    };

    renderPass.Render();
    renderPass.Render();
    renderPass.Render();

    EXPECT_EQ(prepareCallCount, 3);
    EXPECT_EQ(renderCallCount, 3);
}

TEST_F(RenderPassTest, CanCreateRenderPassWithMultipleTextures)
{
    std::unique_ptr<Texture> texture2 = std::make_unique<Texture>(
        TextureId::SsaoNoise,
        1,
        128,
        128,
        GL_RGB,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        GL_NEAREST,
        GL_REPEAT
    );

    std::vector<std::reference_wrapper<const Texture>> textures;
    textures.push_back(std::cref(*texture));
    textures.push_back(std::cref(*texture2));

    EXPECT_NO_THROW(RenderPass renderPass(RenderPassId::Ssao, *shader, *frameBuffer, std::move(textures), []() {}, []() {}));
}

TEST_F(RenderPassTest, CanCreateRenderPassWithNoTextures)
{
    std::vector<std::reference_wrapper<const Texture>> textures;

    EXPECT_NO_THROW(RenderPass renderPass(RenderPassId::Setup, *shader, *frameBuffer, std::move(textures), []() {}, []() {}));
}
