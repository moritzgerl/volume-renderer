#include <gtest/gtest.h>

#include <lights/DirectionalLight.h>

#include <glm/glm.hpp>

class DirectionalLightTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        light = DirectionalLight{};
    }

    DirectionalLight light;
};

TEST_F(DirectionalLightTest, CanCreateDefaultDirectionalLight)
{
    EXPECT_NO_THROW(DirectionalLight defaultLight{});
}

TEST_F(DirectionalLightTest, CanSetDirection)
{
    const glm::vec3 direction{0.0f, -1.0f, 0.0f};
    light.direction = direction;
    EXPECT_EQ(light.direction, direction);
}

TEST_F(DirectionalLightTest, CanSetAmbient)
{
    const glm::vec3 ambient{0.2f, 0.2f, 0.2f};
    light.ambient = ambient;
    EXPECT_EQ(light.ambient, ambient);
}

TEST_F(DirectionalLightTest, CanSetDiffuse)
{
    const glm::vec3 diffuse{0.8f, 0.8f, 0.8f};
    light.diffuse = diffuse;
    EXPECT_EQ(light.diffuse, diffuse);
}

TEST_F(DirectionalLightTest, CanSetSpecular)
{
    const glm::vec3 specular{1.0f, 1.0f, 1.0f};
    light.specular = specular;
    EXPECT_EQ(light.specular, specular);
}

TEST_F(DirectionalLightTest, CanSetIntensity)
{
    const float intensity = 1.5f;
    light.intensity = intensity;
    EXPECT_FLOAT_EQ(light.intensity, intensity);
}

TEST_F(DirectionalLightTest, CanSetAllParameters)
{
    light.direction = glm::vec3{1.0f, -1.0f, 0.0f};
    light.ambient = glm::vec3{0.1f, 0.1f, 0.1f};
    light.diffuse = glm::vec3{0.7f, 0.7f, 0.7f};
    light.specular = glm::vec3{0.9f, 0.9f, 0.9f};
    light.intensity = 2.0f;

    EXPECT_EQ(light.direction, glm::vec3(1.0f, -1.0f, 0.0f));
    EXPECT_EQ(light.ambient, glm::vec3(0.1f, 0.1f, 0.1f));
    EXPECT_EQ(light.diffuse, glm::vec3(0.7f, 0.7f, 0.7f));
    EXPECT_EQ(light.specular, glm::vec3(0.9f, 0.9f, 0.9f));
    EXPECT_FLOAT_EQ(light.intensity, 2.0f);
}
