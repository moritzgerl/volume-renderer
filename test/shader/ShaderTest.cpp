#include <gtest/gtest.h>

#include <context/GlfwWindow.h>
#include <context/InitGl.h>
#include <shader/Shader.h>

#include <glad/glad.h>
#include <memory>

class ShaderTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        window = std::make_unique<Context::GlfwWindow>();
        Context::InitGl();
    }

    std::unique_ptr<Context::GlfwWindow> window;
};

TEST_F(ShaderTest, CanCreateShaderWithVertexAndFragmentShaders)
{
    EXPECT_NO_THROW(Shader shader(ShaderId::Volume, "src/shaders/Volume.vert", "src/shaders/Volume.frag"));
}

TEST_F(ShaderTest, GetIdReturnsCorrectId)
{
    Shader shader{ShaderId::Volume, "src/shaders/Volume.vert", "src/shaders/Volume.frag"};
    EXPECT_EQ(shader.GetId(), ShaderId::Volume);
}

TEST_F(ShaderTest, GetIdReturnsCorrectIdForDifferentShader)
{
    Shader shader{ShaderId::DebugQuad, "src/shaders/debug_quad.vert", "src/shaders/debug_quad.frag"};
    EXPECT_EQ(shader.GetId(), ShaderId::DebugQuad);
}

TEST_F(ShaderTest, CanUseShader)
{
    Shader shader{ShaderId::Volume, "src/shaders/Volume.vert", "src/shaders/Volume.frag"};
    EXPECT_NO_THROW(shader.Use());
}

TEST_F(ShaderTest, UseDoesNotCauseGLError)
{
    Shader shader{ShaderId::Volume, "src/shaders/Volume.vert", "src/shaders/Volume.frag"};
    shader.Use();
    EXPECT_EQ(glGetError(), GL_NO_ERROR);
}

TEST_F(ShaderTest, CanSetBoolUniform)
{
    Shader shader{ShaderId::Volume, "src/shaders/Volume.vert", "src/shaders/Volume.frag"};
    shader.Use();
    EXPECT_NO_THROW(shader.SetBool("someUniform", true));
}

TEST_F(ShaderTest, CanSetIntUniform)
{
    Shader shader{ShaderId::Volume, "src/shaders/Volume.vert", "src/shaders/Volume.frag"};
    shader.Use();
    EXPECT_NO_THROW(shader.SetInt("someUniform", 42));
}

TEST_F(ShaderTest, CanSetFloatUniform)
{
    Shader shader{ShaderId::Volume, "src/shaders/Volume.vert", "src/shaders/Volume.frag"};
    shader.Use();
    EXPECT_NO_THROW(shader.SetFloat("someUniform", 3.14f));
}

TEST_F(ShaderTest, CanSetVec2Uniform)
{
    Shader shader{ShaderId::Volume, "src/shaders/Volume.vert", "src/shaders/Volume.frag"};
    shader.Use();
    EXPECT_NO_THROW(shader.SetVec2("someUniform", glm::vec2{1.0f, 2.0f}));
}

TEST_F(ShaderTest, CanSetVec2UniformWithComponents)
{
    Shader shader{ShaderId::Volume, "src/shaders/Volume.vert", "src/shaders/Volume.frag"};
    shader.Use();
    EXPECT_NO_THROW(shader.SetVec2("someUniform", 1.0f, 2.0f));
}

TEST_F(ShaderTest, CanSetVec3Uniform)
{
    Shader shader{ShaderId::Volume, "src/shaders/Volume.vert", "src/shaders/Volume.frag"};
    shader.Use();
    EXPECT_NO_THROW(shader.SetVec3("someUniform", glm::vec3{1.0f, 2.0f, 3.0f}));
}

TEST_F(ShaderTest, CanSetVec3UniformWithComponents)
{
    Shader shader{ShaderId::Volume, "src/shaders/Volume.vert", "src/shaders/Volume.frag"};
    shader.Use();
    EXPECT_NO_THROW(shader.SetVec3("someUniform", 1.0f, 2.0f, 3.0f));
}

TEST_F(ShaderTest, CanSetVec4Uniform)
{
    Shader shader{ShaderId::Volume, "src/shaders/Volume.vert", "src/shaders/Volume.frag"};
    shader.Use();
    EXPECT_NO_THROW(shader.SetVec4("someUniform", glm::vec4{1.0f, 2.0f, 3.0f, 4.0f}));
}

TEST_F(ShaderTest, CanSetVec4UniformWithComponents)
{
    Shader shader{ShaderId::Volume, "src/shaders/Volume.vert", "src/shaders/Volume.frag"};
    shader.Use();
    EXPECT_NO_THROW(shader.SetVec4("someUniform", 1.0f, 2.0f, 3.0f, 4.0f));
}

TEST_F(ShaderTest, CanSetMat2Uniform)
{
    Shader shader{ShaderId::Volume, "src/shaders/Volume.vert", "src/shaders/Volume.frag"};
    shader.Use();
    glm::mat2 mat{1.0f};
    EXPECT_NO_THROW(shader.SetMat2("someUniform", mat));
}

TEST_F(ShaderTest, CanSetMat3Uniform)
{
    Shader shader{ShaderId::Volume, "src/shaders/Volume.vert", "src/shaders/Volume.frag"};
    shader.Use();
    glm::mat3 mat{1.0f};
    EXPECT_NO_THROW(shader.SetMat3("someUniform", mat));
}

TEST_F(ShaderTest, CanSetMat4Uniform)
{
    Shader shader{ShaderId::Volume, "src/shaders/Volume.vert", "src/shaders/Volume.frag"};
    shader.Use();
    glm::mat4 mat{1.0f};
    EXPECT_NO_THROW(shader.SetMat4("someUniform", mat));
}

TEST_F(ShaderTest, CanCreateMultipleShaders)
{
    Shader shader1{ShaderId::Volume, "src/shaders/Volume.vert", "src/shaders/Volume.frag"};
    Shader shader2{ShaderId::DebugQuad, "src/shaders/DebugQuad.vert", "src/shaders/DebugQuadColor.frag"};

    EXPECT_EQ(shader1.GetId(), ShaderId::Volume);
    EXPECT_EQ(shader2.GetId(), ShaderId::DebugQuad);
}

TEST_F(ShaderTest, CanSwitchBetweenShaders)
{
    Shader shader1{ShaderId::Volume, "src/shaders/Volume.vert", "src/shaders/Volume.frag"};
    Shader shader2{ShaderId::DebugQuad, "src/shaders/DebugQuad.vert", "src/shaders/DebugQuadColor.frag"};

    EXPECT_NO_THROW(shader1.Use());
    EXPECT_NO_THROW(shader2.Use());
    EXPECT_NO_THROW(shader1.Use());
}
