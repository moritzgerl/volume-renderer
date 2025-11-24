#include <gtest/gtest.h>

#include <context/GlfwWindow.h>
#include <context/InitGl.h>
#include <gui/GuiParameters.h>
#include <gui/MakeDefaultGuiParameters.h>
#include <shader/Shader.h>
#include <shader/UpdateLightingParametersInShader.h>
#include <utils/FileSystem.h>

#include <memory>

class UpdateLightingParametersInShaderTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        window = std::make_unique<Context::GlfwWindow>();
        Context::InitGl();

        guiParameters = Factory::MakeDefaultGuiParameters();
        shader = std::make_unique<Shader>(ShaderId::Volume, FileSystem::GetPath("src/shaders/Volume.vert").c_str(), FileSystem::GetPath("src/shaders/Volume.frag").c_str());
    }

    std::unique_ptr<Context::GlfwWindow> window;
    GuiParameters guiParameters;
    std::unique_ptr<Shader> shader;
};

TEST_F(UpdateLightingParametersInShaderTest, CanCallUpdateLightingParametersInShader)
{
    shader->Use();
    EXPECT_NO_THROW(ShaderUtils::UpdateLightingParametersInShader(guiParameters, *shader));
}

TEST_F(UpdateLightingParametersInShaderTest, UpdateLightingParametersDoesNotCauseGLError)
{
    shader->Use();
    ShaderUtils::UpdateLightingParametersInShader(guiParameters, *shader);
    EXPECT_EQ(glGetError(), GL_NO_ERROR);
}

TEST_F(UpdateLightingParametersInShaderTest, CanUpdateWithModifiedDirectionalLight)
{
    guiParameters.directionalLight.direction = glm::vec3{1.0f, -1.0f, 0.0f};
    guiParameters.directionalLight.intensity = 2.0f;

    shader->Use();
    EXPECT_NO_THROW(ShaderUtils::UpdateLightingParametersInShader(guiParameters, *shader));
}

TEST_F(UpdateLightingParametersInShaderTest, CanUpdateWithModifiedPointLights)
{
    guiParameters.pointLights[0].position = glm::vec3{5.0f, 5.0f, 5.0f};
    guiParameters.pointLights[0].intensity = 1.5f;

    shader->Use();
    EXPECT_NO_THROW(ShaderUtils::UpdateLightingParametersInShader(guiParameters, *shader));
}

TEST_F(UpdateLightingParametersInShaderTest, CanUpdateMultipleTimes)
{
    shader->Use();
    ShaderUtils::UpdateLightingParametersInShader(guiParameters, *shader);

    guiParameters.directionalLight.intensity = 2.0f;
    ShaderUtils::UpdateLightingParametersInShader(guiParameters, *shader);

    guiParameters.pointLights[0].intensity = 1.5f;
    ShaderUtils::UpdateLightingParametersInShader(guiParameters, *shader);

    EXPECT_EQ(glGetError(), GL_NO_ERROR);
}
