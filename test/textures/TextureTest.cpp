#include <gtest/gtest.h>

#include <context/GlfwWindow.h>
#include <context/InitGl.h>
#include <textures/Texture.h>
#include <textures/TextureId.h>
#include <textures/TextureType.h>

#include <glad/glad.h>
#include <memory>

class TextureTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        window = std::make_unique<Context::GlfwWindow>();
        Context::InitGl();
    }

    std::unique_ptr<Context::GlfwWindow> window;
};

TEST_F(TextureTest, CanCreate1DTextureWithData)
{
    unsigned char data[256 * 4] = {0};
    EXPECT_NO_THROW(Texture texture(
        TextureId::TransferFunction,
        GL_TEXTURE0,
        256,
        GL_RGBA,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        GL_LINEAR,
        GL_CLAMP_TO_EDGE,
        data
    ));
}

TEST_F(TextureTest, CanCreate2DTextureWithoutData)
{
    EXPECT_NO_THROW(Texture texture(
        TextureId::SsaoPosition,
        GL_TEXTURE1,
        800,
        600,
        GL_RGBA32F,
        GL_RGBA,
        GL_FLOAT,
        GL_NEAREST,
        GL_CLAMP_TO_EDGE
    ));
}

TEST_F(TextureTest, CanCreate2DTextureWithData)
{
    unsigned char data[4 * 4 * 4] = {0};
    EXPECT_NO_THROW(Texture texture(
        TextureId::SsaoNoise,
        GL_TEXTURE2,
        4,
        4,
        GL_RGBA32F,
        GL_RGB,
        GL_FLOAT,
        GL_NEAREST,
        GL_REPEAT,
        data
    ));
}

TEST_F(TextureTest, CanCreate3DTextureWithData)
{
    unsigned char data[8 * 8 * 8] = {0};
    EXPECT_NO_THROW(Texture texture(
        TextureId::VolumeData,
        GL_TEXTURE3,
        8,
        8,
        8,
        GL_R16,
        GL_RED,
        GL_UNSIGNED_SHORT,
        GL_LINEAR,
        GL_CLAMP_TO_EDGE,
        data
    ));
}

TEST_F(TextureTest, GetIdReturnsCorrectId)
{
    unsigned char data[256 * 4] = {0};
    Texture texture{
        TextureId::TransferFunction,
        GL_TEXTURE0,
        256,
        GL_RGBA,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        GL_LINEAR,
        GL_CLAMP_TO_EDGE,
        data
    };

    EXPECT_EQ(texture.GetId(), TextureId::TransferFunction);
}

TEST_F(TextureTest, GetTextureTypeReturns1DFor1DTexture)
{
    unsigned char data[256 * 4] = {0};
    Texture texture{
        TextureId::TransferFunction,
        GL_TEXTURE0,
        256,
        GL_RGBA,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        GL_LINEAR,
        GL_CLAMP_TO_EDGE,
        data
    };

    EXPECT_EQ(texture.GetTextureType(), TextureType::Texture1D);
}

TEST_F(TextureTest, GetTextureTypeReturns2DFor2DTexture)
{
    Texture texture{
        TextureId::SsaoPosition,
        GL_TEXTURE1,
        800,
        600,
        GL_RGBA32F,
        GL_RGBA,
        GL_FLOAT,
        GL_NEAREST,
        GL_CLAMP_TO_EDGE
    };

    EXPECT_EQ(texture.GetTextureType(), TextureType::Texture2D);
}

TEST_F(TextureTest, GetTextureTypeReturns3DFor3DTexture)
{
    unsigned char data[8 * 8 * 8] = {0};
    Texture texture{
        TextureId::VolumeData,
        GL_TEXTURE3,
        8,
        8,
        8,
        GL_R16,
        GL_RED,
        GL_UNSIGNED_SHORT,
        GL_LINEAR,
        GL_CLAMP_TO_EDGE,
        data
    };

    EXPECT_EQ(texture.GetTextureType(), TextureType::Texture3D);
}

TEST_F(TextureTest, GetTextureUnitReturnsCorrectUnit)
{
    unsigned char data[256 * 4] = {0};
    Texture texture{
        TextureId::TransferFunction,
        GL_TEXTURE5,
        256,
        GL_RGBA,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        GL_LINEAR,
        GL_CLAMP_TO_EDGE,
        data
    };

    EXPECT_EQ(texture.GetTextureUnit(), 5u);
}

TEST_F(TextureTest, GetTextureUnitEnumReturnsCorrectEnum)
{
    unsigned char data[256 * 4] = {0};
    Texture texture{
        TextureId::TransferFunction,
        GL_TEXTURE0,
        256,
        GL_RGBA,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        GL_LINEAR,
        GL_CLAMP_TO_EDGE,
        data
    };

    EXPECT_EQ(texture.GetTextureUnitEnum(), GL_TEXTURE0);
}

TEST_F(TextureTest, GetGlIdReturnsNonZero)
{
    unsigned char data[256 * 4] = {0};
    Texture texture{
        TextureId::TransferFunction,
        GL_TEXTURE0,
        256,
        GL_RGBA,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        GL_LINEAR,
        GL_CLAMP_TO_EDGE,
        data
    };

    EXPECT_NE(texture.GetGlId(), 0u);
}

TEST_F(TextureTest, CanBindTexture)
{
    unsigned char data[256 * 4] = {0};
    Texture texture{
        TextureId::TransferFunction,
        GL_TEXTURE0,
        256,
        GL_RGBA,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        GL_LINEAR,
        GL_CLAMP_TO_EDGE,
        data
    };

    EXPECT_NO_THROW(texture.Bind());
}

TEST_F(TextureTest, BindDoesNotCauseGLError)
{
    unsigned char data[256 * 4] = {0};
    Texture texture{
        TextureId::TransferFunction,
        GL_TEXTURE0,
        256,
        GL_RGBA,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        GL_LINEAR,
        GL_CLAMP_TO_EDGE,
        data
    };

    texture.Bind();
    EXPECT_EQ(glGetError(), GL_NO_ERROR);
}

TEST_F(TextureTest, CanAddBorder)
{
    unsigned char data[256 * 4] = {0};
    Texture texture{
        TextureId::TransferFunction,
        GL_TEXTURE0,
        256,
        GL_RGBA,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        GL_LINEAR,
        GL_CLAMP_TO_EDGE,
        data
    };

    EXPECT_NO_THROW(texture.AddBorder());
}

TEST_F(TextureTest, CanCreateMultipleTextures)
{
    unsigned char data1[256 * 4] = {0};
    unsigned char data2[4 * 4 * 4] = {0};

    Texture texture1{
        TextureId::TransferFunction,
        GL_TEXTURE0,
        256,
        GL_RGBA,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        GL_LINEAR,
        GL_CLAMP_TO_EDGE,
        data1
    };

    Texture texture2{
        TextureId::SsaoNoise,
        GL_TEXTURE1,
        4,
        4,
        GL_RGBA32F,
        GL_RGB,
        GL_FLOAT,
        GL_NEAREST,
        GL_REPEAT,
        data2
    };

    EXPECT_EQ(texture1.GetId(), TextureId::TransferFunction);
    EXPECT_EQ(texture2.GetId(), TextureId::SsaoNoise);
}

TEST_F(TextureTest, CanBindMultipleTextures)
{
    unsigned char data1[256 * 4] = {0};
    unsigned char data2[4 * 4 * 4] = {0};

    Texture texture1{
        TextureId::TransferFunction,
        GL_TEXTURE0,
        256,
        GL_RGBA,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        GL_LINEAR,
        GL_CLAMP_TO_EDGE,
        data1
    };

    Texture texture2{
        TextureId::SsaoNoise,
        GL_TEXTURE1,
        4,
        4,
        GL_RGBA32F,
        GL_RGB,
        GL_FLOAT,
        GL_NEAREST,
        GL_REPEAT,
        data2
    };

    EXPECT_NO_THROW(texture1.Bind());
    EXPECT_NO_THROW(texture2.Bind());
}
