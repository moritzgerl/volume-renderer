#include <gtest/gtest.h>

#include <buffers/FrameBuffer.h>
#include <buffers/FrameBufferId.h>
#include <context/GlfwWindow.h>
#include <context/InitGl.h>
#include <shader/Shader.h>
#include <shader/ShaderId.h>
#include <storage/ElementStorage.h>
#include <textures/Texture.h>
#include <textures/TextureId.h>

#include <glad/glad.h>
#include <memory>
#include <vector>

class ElementStorageTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        window = std::make_unique<Context::GlfwWindow>();
        Context::InitGl();
    }

    std::unique_ptr<Context::GlfwWindow> window;
};

TEST_F(ElementStorageTest, CanCreateShaderStorage)
{
    std::vector<Shader> shaders;
    shaders.emplace_back(ShaderId::Volume, "src/shaders/Volume.vert", "src/shaders/Volume.frag");

    using ShaderStorage = ElementStorage<Shader, ShaderId>;
    EXPECT_NO_THROW(ShaderStorage storage(std::move(shaders)));
}

TEST_F(ElementStorageTest, CanGetShaderByIdFromShaderStorage)
{
    std::vector<Shader> shaders;
    shaders.emplace_back(ShaderId::Volume, "src/shaders/Volume.vert", "src/shaders/Volume.frag");
    shaders.emplace_back(ShaderId::Ssao, "src/shaders/Ssao.vert", "src/shaders/Ssao.frag");

    ElementStorage<Shader, ShaderId> storage{std::move(shaders)};

    const Shader& volumeShader = storage.GetElement(ShaderId::Volume);
    EXPECT_EQ(volumeShader.GetId(), ShaderId::Volume);

    const Shader& ssaoShader = storage.GetElement(ShaderId::Ssao);
    EXPECT_EQ(ssaoShader.GetId(), ShaderId::Ssao);
}

TEST_F(ElementStorageTest, CanGetMutableShaderFromShaderStorage)
{
    std::vector<Shader> shaders;
    shaders.emplace_back(ShaderId::Volume, "src/shaders/Volume.vert", "src/shaders/Volume.frag");

    ElementStorage<Shader, ShaderId> storage{std::move(shaders)};

    Shader& shader = storage.GetElement(ShaderId::Volume);
    EXPECT_EQ(shader.GetId(), ShaderId::Volume);
    EXPECT_NO_THROW(shader.Use());
}

TEST_F(ElementStorageTest, CanGetAllShadersFromShaderStorage)
{
    std::vector<Shader> shaders;
    shaders.emplace_back(ShaderId::Volume, "src/shaders/Volume.vert", "src/shaders/Volume.frag");
    shaders.emplace_back(ShaderId::Ssao, "src/shaders/Ssao.vert", "src/shaders/Ssao.frag");

    ElementStorage<Shader, ShaderId> storage{std::move(shaders)};

    const std::vector<Shader>& allShaders = storage.GetElements();
    EXPECT_EQ(allShaders.size(), 2u);
}

TEST_F(ElementStorageTest, CanCreateTextureStorage)
{
    std::vector<Texture> textures;
    textures.emplace_back(TextureId::TransferFunction, 0, 256, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, GL_LINEAR, GL_CLAMP_TO_EDGE, nullptr);

    using TextureStorage = ElementStorage<Texture, TextureId>;
    EXPECT_NO_THROW(TextureStorage storage(std::move(textures)));
}

TEST_F(ElementStorageTest, CanGetTextureByIdFromTextureStorage)
{
    std::vector<Texture> textures;
    textures.emplace_back(TextureId::TransferFunction, 0, 256, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, GL_LINEAR, GL_CLAMP_TO_EDGE, nullptr);
    textures.emplace_back(TextureId::SsaoNoise, 1, 4, 4, GL_RGBA32F, GL_RGB, GL_FLOAT, GL_NEAREST, GL_REPEAT);

    ElementStorage<Texture, TextureId> storage{std::move(textures)};

    const Texture& transferFunctionTexture = storage.GetElement(TextureId::TransferFunction);
    EXPECT_EQ(transferFunctionTexture.GetId(), TextureId::TransferFunction);

    const Texture& noiseTexture = storage.GetElement(TextureId::SsaoNoise);
    EXPECT_EQ(noiseTexture.GetId(), TextureId::SsaoNoise);
}

TEST_F(ElementStorageTest, CanGetMutableTextureFromTextureStorage)
{
    std::vector<Texture> textures;
    textures.emplace_back(TextureId::TransferFunction, 0, 256, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, GL_LINEAR, GL_CLAMP_TO_EDGE, nullptr);

    ElementStorage<Texture, TextureId> storage{std::move(textures)};

    Texture& texture = storage.GetElement(TextureId::TransferFunction);
    EXPECT_EQ(texture.GetId(), TextureId::TransferFunction);
    EXPECT_NO_THROW(texture.Bind());
}

TEST_F(ElementStorageTest, CanGetAllTexturesFromTextureStorage)
{
    std::vector<Texture> textures;
    textures.emplace_back(TextureId::TransferFunction, 0, 256, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, GL_LINEAR, GL_CLAMP_TO_EDGE, nullptr);
    textures.emplace_back(TextureId::SsaoNoise, 1, 4, 4, GL_RGBA32F, GL_RGB, GL_FLOAT, GL_NEAREST, GL_REPEAT);

    ElementStorage<Texture, TextureId> storage{std::move(textures)};

    const std::vector<Texture>& allTextures = storage.GetElements();
    EXPECT_EQ(allTextures.size(), 2u);
}

TEST_F(ElementStorageTest, CanCreateFrameBufferStorage)
{
    std::vector<FrameBuffer> frameBuffers;
    frameBuffers.emplace_back(FrameBufferId::Default);

    using FrameBufferStorage = ElementStorage<FrameBuffer, FrameBufferId>;
    EXPECT_NO_THROW(FrameBufferStorage storage(std::move(frameBuffers)));
}

TEST_F(ElementStorageTest, CanGetFrameBufferByIdFromFrameBufferStorage)
{
    std::vector<FrameBuffer> frameBuffers;
    frameBuffers.emplace_back(FrameBufferId::Default);
    frameBuffers.emplace_back(FrameBufferId::Ssao);

    ElementStorage<FrameBuffer, FrameBufferId> storage{std::move(frameBuffers)};

    const FrameBuffer& defaultFB = storage.GetElement(FrameBufferId::Default);
    EXPECT_EQ(defaultFB.GetId(), FrameBufferId::Default);

    const FrameBuffer& ssaoFB = storage.GetElement(FrameBufferId::Ssao);
    EXPECT_EQ(ssaoFB.GetId(), FrameBufferId::Ssao);
}

TEST_F(ElementStorageTest, CanGetMutableFrameBufferFromFrameBufferStorage)
{
    std::vector<FrameBuffer> frameBuffers;
    frameBuffers.emplace_back(FrameBufferId::Default);

    ElementStorage<FrameBuffer, FrameBufferId> storage{std::move(frameBuffers)};

    FrameBuffer& fb = storage.GetElement(FrameBufferId::Default);
    EXPECT_EQ(fb.GetId(), FrameBufferId::Default);
    EXPECT_NO_THROW(fb.Bind());
}

TEST_F(ElementStorageTest, CanGetAllFrameBuffersFromFrameBufferStorage)
{
    std::vector<FrameBuffer> frameBuffers;
    frameBuffers.emplace_back(FrameBufferId::Default);
    frameBuffers.emplace_back(FrameBufferId::Ssao);

    ElementStorage<FrameBuffer, FrameBufferId> storage{std::move(frameBuffers)};

    const std::vector<FrameBuffer>& allFrameBuffers = storage.GetElements();
    EXPECT_EQ(allFrameBuffers.size(), 2u);
}

TEST_F(ElementStorageTest, GetElementReturnsFirstElementWhenIdNotFound)
{
    std::vector<Shader> shaders;
    shaders.emplace_back(ShaderId::Volume, "src/shaders/Volume.vert", "src/shaders/Volume.frag");

    ElementStorage<Shader, ShaderId> storage{std::move(shaders)};

    // Request a shader that doesn't exist - should return first element
    const Shader& shader = storage.GetElement(ShaderId::Unknown);
    EXPECT_EQ(shader.GetId(), ShaderId::Volume);
}
