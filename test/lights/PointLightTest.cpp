#include <gtest/gtest.h>

#include <lights/PointLight.h>

#include <glm/glm.hpp>

class PointLightTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        light = PointLight{};
    }

    PointLight light;
};

TEST_F(PointLightTest, CanCreateDefaultPointLight)
{
    EXPECT_NO_THROW(PointLight defaultLight{});
}

TEST_F(PointLightTest, CanSetPosition)
{
    const glm::vec3 position{1.0f, 2.0f, 3.0f};
    light.position = position;
    EXPECT_EQ(light.position, position);
}

TEST_F(PointLightTest, CanSetAmbient)
{
    const glm::vec3 ambient{0.2f, 0.2f, 0.2f};
    light.ambient = ambient;
    EXPECT_EQ(light.ambient, ambient);
}

TEST_F(PointLightTest, CanSetDiffuse)
{
    const glm::vec3 diffuse{0.8f, 0.8f, 0.8f};
    light.diffuse = diffuse;
    EXPECT_EQ(light.diffuse, diffuse);
}

TEST_F(PointLightTest, CanSetSpecular)
{
    const glm::vec3 specular{1.0f, 1.0f, 1.0f};
    light.specular = specular;
    EXPECT_EQ(light.specular, specular);
}

TEST_F(PointLightTest, CanSetIntensity)
{
    const float intensity = 1.5f;
    light.intensity = intensity;
    EXPECT_FLOAT_EQ(light.intensity, intensity);
}

TEST_F(PointLightTest, CanSetAllParameters)
{
    light.position = glm::vec3{5.0f, 10.0f, 15.0f};
    light.ambient = glm::vec3{0.1f, 0.1f, 0.1f};
    light.diffuse = glm::vec3{0.7f, 0.7f, 0.7f};
    light.specular = glm::vec3{0.9f, 0.9f, 0.9f};
    light.intensity = 2.0f;

    EXPECT_EQ(light.position, glm::vec3(5.0f, 10.0f, 15.0f));
    EXPECT_EQ(light.ambient, glm::vec3(0.1f, 0.1f, 0.1f));
    EXPECT_EQ(light.diffuse, glm::vec3(0.7f, 0.7f, 0.7f));
    EXPECT_EQ(light.specular, glm::vec3(0.9f, 0.9f, 0.9f));
    EXPECT_FLOAT_EQ(light.intensity, 2.0f);
}

TEST_F(PointLightTest, CanCreateMultiplePointLights)
{
    PointLight light1{};
    light1.position = glm::vec3{1.0f, 0.0f, 0.0f};
    light1.intensity = 1.0f;

    PointLight light2{};
    light2.position = glm::vec3{-1.0f, 0.0f, 0.0f};
    light2.intensity = 2.0f;

    EXPECT_NE(light1.position, light2.position);
    EXPECT_NE(light1.intensity, light2.intensity);
}
