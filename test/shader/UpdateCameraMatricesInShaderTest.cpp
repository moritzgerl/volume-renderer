#include <gtest/gtest.h>

#include <camera/Camera.h>
#include <camera/CameraParameters.h>
#include <context/GlfwWindow.h>
#include <context/InitGl.h>
#include <shader/GetShaderSource.h>
#include <shader/Shader.h>
#include <shader/ShaderType.h>
#include <shader/UpdateCameraMatricesInShader.h>

#include <memory>
#include <string>

namespace
{
    std::string GetShaderSourceOrThrow(ShaderId shaderId, ShaderType shaderType)
    {
        const auto result = ShaderSource::GetShaderSource(shaderId, shaderType);
        if (!result.has_value())
        {
            throw std::runtime_error{"Failed to load shader"};
        }
        return result.value();
    }
}

class UpdateCameraMatricesInShaderTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        window = std::make_unique<Context::GlfwWindow>();
        Context::InitGl();

        CameraParameters params{};
        params.position = glm::vec3{0.0f, 0.0f, 3.0f};
        params.zoom = 45.0f;

        camera = std::make_unique<Camera>(params);
        shader = std::make_unique<Shader>(ShaderId::Volume, GetShaderSourceOrThrow(ShaderId::Volume, ShaderType::Vertex), GetShaderSourceOrThrow(ShaderId::Volume, ShaderType::Fragment));
    }

    std::unique_ptr<Context::GlfwWindow> window;
    std::unique_ptr<Camera> camera;
    std::unique_ptr<Shader> shader;
};

TEST_F(UpdateCameraMatricesInShaderTest, CanCallUpdateCameraMatricesInShader)
{
    shader->Use();
    EXPECT_NO_THROW(ShaderUtils::UpdateCameraMatricesInShader(*camera, *shader, 800.0f, 600.0f));
}

TEST_F(UpdateCameraMatricesInShaderTest, UpdateCameraMatricesDoesNotCauseGLError)
{
    shader->Use();
    ShaderUtils::UpdateCameraMatricesInShader(*camera, *shader, 800.0f, 600.0f);
    EXPECT_EQ(glGetError(), GL_NO_ERROR);
}

TEST_F(UpdateCameraMatricesInShaderTest, CanUpdateWithDifferentViewportDimensions)
{
    shader->Use();
    EXPECT_NO_THROW(ShaderUtils::UpdateCameraMatricesInShader(*camera, *shader, 1920.0f, 1080.0f));
}

TEST_F(UpdateCameraMatricesInShaderTest, CanUpdateMultipleTimes)
{
    shader->Use();
    ShaderUtils::UpdateCameraMatricesInShader(*camera, *shader, 800.0f, 600.0f);
    ShaderUtils::UpdateCameraMatricesInShader(*camera, *shader, 1024.0f, 768.0f);
    ShaderUtils::UpdateCameraMatricesInShader(*camera, *shader, 1920.0f, 1080.0f);
    EXPECT_EQ(glGetError(), GL_NO_ERROR);
}

TEST_F(UpdateCameraMatricesInShaderTest, CanUpdateWithDifferentCamera)
{
    CameraParameters params{};
    params.position = glm::vec3{5.0f, 5.0f, 5.0f};
    params.zoom = 60.0f;

    Camera camera2{params};
    shader->Use();

    EXPECT_NO_THROW(ShaderUtils::UpdateCameraMatricesInShader(*camera, *shader, 800.0f, 600.0f));
    EXPECT_NO_THROW(ShaderUtils::UpdateCameraMatricesInShader(camera2, *shader, 800.0f, 600.0f));
}
