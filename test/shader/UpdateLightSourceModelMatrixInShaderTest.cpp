#include <gtest/gtest.h>

#include <context/GlfwWindow.h>
#include <context/InitGl.h>
#include <shader/LoadShader.h>
#include <shader/Shader.h>
#include <shader/ShaderType.h>
#include <shader/UpdateLightSourceModelMatrixInShader.h>

#include <glm/glm.hpp>
#include <memory>
#include <string>

namespace
{
    std::string LoadShaderOrThrow(ShaderId shaderId, ShaderType shaderType)
    {
        const auto result = ShaderSource::LoadShader(shaderId, shaderType);
        if (!result.has_value())
        {
            throw std::runtime_error{"Failed to load shader"};
        }
        return result.value();
    }
}

class UpdateLightSourceModelMatrixInShaderTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        window = std::make_unique<Context::GlfwWindow>();
        Context::InitGl();

        shader = std::make_unique<Shader>(ShaderId::LightSource, LoadShaderOrThrow(ShaderId::LightSource, ShaderType::Vertex), LoadShaderOrThrow(ShaderId::LightSource, ShaderType::Fragment));
    }

    std::unique_ptr<Context::GlfwWindow> window;
    std::unique_ptr<Shader> shader;
};

TEST_F(UpdateLightSourceModelMatrixInShaderTest, CanCallUpdateLightSourceModelMatrixInShader)
{
    shader->Use();
    glm::vec3 lightPosition{1.0f, 2.0f, 3.0f};
    EXPECT_NO_THROW(ShaderUtils::UpdateLightSourceModelMatrixInShader(lightPosition, *shader));
}

TEST_F(UpdateLightSourceModelMatrixInShaderTest, UpdateLightSourceModelMatrixDoesNotCauseGLError)
{
    shader->Use();
    glm::vec3 lightPosition{1.0f, 2.0f, 3.0f};
    ShaderUtils::UpdateLightSourceModelMatrixInShader(lightPosition, *shader);
    EXPECT_EQ(glGetError(), GL_NO_ERROR);
}

TEST_F(UpdateLightSourceModelMatrixInShaderTest, CanUpdateWithDifferentPositions)
{
    shader->Use();

    glm::vec3 position1{0.0f, 0.0f, 0.0f};
    glm::vec3 position2{5.0f, 5.0f, 5.0f};
    glm::vec3 position3{-3.0f, 2.0f, -1.0f};

    EXPECT_NO_THROW(ShaderUtils::UpdateLightSourceModelMatrixInShader(position1, *shader));
    EXPECT_NO_THROW(ShaderUtils::UpdateLightSourceModelMatrixInShader(position2, *shader));
    EXPECT_NO_THROW(ShaderUtils::UpdateLightSourceModelMatrixInShader(position3, *shader));
}

TEST_F(UpdateLightSourceModelMatrixInShaderTest, CanUpdateMultipleTimes)
{
    shader->Use();
    glm::vec3 lightPosition{1.0f, 2.0f, 3.0f};

    ShaderUtils::UpdateLightSourceModelMatrixInShader(lightPosition, *shader);
    ShaderUtils::UpdateLightSourceModelMatrixInShader(lightPosition, *shader);
    ShaderUtils::UpdateLightSourceModelMatrixInShader(lightPosition, *shader);

    EXPECT_EQ(glGetError(), GL_NO_ERROR);
}

TEST_F(UpdateLightSourceModelMatrixInShaderTest, CanUpdateWithOriginPosition)
{
    shader->Use();
    glm::vec3 origin{0.0f, 0.0f, 0.0f};
    EXPECT_NO_THROW(ShaderUtils::UpdateLightSourceModelMatrixInShader(origin, *shader));
}

TEST_F(UpdateLightSourceModelMatrixInShaderTest, CanUpdateWithNegativePosition)
{
    shader->Use();
    glm::vec3 negativePosition{-5.0f, -3.0f, -2.0f};
    EXPECT_NO_THROW(ShaderUtils::UpdateLightSourceModelMatrixInShader(negativePosition, *shader));
}
