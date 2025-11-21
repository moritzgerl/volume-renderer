#include <gtest/gtest.h>

#include <textures/TextureUnitMapping.h>

#include <glad/glad.h>

TEST(TextureUnitMappingTest, CanConvertGLTexture0ToZero)
{
    const unsigned int result = TextureUnitMapping::GLenumToUnsignedInt(GL_TEXTURE0);
    EXPECT_EQ(result, 0u);
}

TEST(TextureUnitMappingTest, CanConvertGLTexture1ToOne)
{
    const unsigned int result = TextureUnitMapping::GLenumToUnsignedInt(GL_TEXTURE1);
    EXPECT_EQ(result, 1u);
}

TEST(TextureUnitMappingTest, CanConvertGLTexture5ToFive)
{
    const unsigned int result = TextureUnitMapping::GLenumToUnsignedInt(GL_TEXTURE5);
    EXPECT_EQ(result, 5u);
}

TEST(TextureUnitMappingTest, CanConvertGLTexture15To15)
{
    const unsigned int result = TextureUnitMapping::GLenumToUnsignedInt(GL_TEXTURE15);
    EXPECT_EQ(result, 15u);
}

TEST(TextureUnitMappingTest, CanConvertGLTexture31To31)
{
    // GL_TEXTURE31 converts to 31 using arithmetic (GL_TEXTURE31 - GL_TEXTURE0)
    const unsigned int result = TextureUnitMapping::GLenumToUnsignedInt(GL_TEXTURE31);
    EXPECT_EQ(result, 31u);
}
