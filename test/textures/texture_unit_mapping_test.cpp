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

TEST(TextureUnitMappingTest, CanConvertUnmappedTextureUnitToZero)
{
    // GL_TEXTURE31 is not in the mapping, so it should return 0
    const unsigned int result = TextureUnitMapping::GLenumToUnsignedInt(GL_TEXTURE31);
    EXPECT_EQ(result, 0u);
}
