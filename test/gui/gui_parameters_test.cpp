#include <gtest/gtest.h>

#include <gui/GuiParameters.h>
#include <lights/DirectionalLight.h>
#include <lights/PointLight.h>
#include <transferfunction/TransferFunction.h>

#include <glm/glm.hpp>

class GuiParametersTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        guiParameters = GuiParameters{};
    }

    GuiParameters guiParameters;
};

TEST_F(GuiParametersTest, CanCreateDefaultGuiParameters)
{
    EXPECT_NO_THROW(GuiParameters params{});
}

TEST_F(GuiParametersTest, CanSetAndGetShowLightSources)
{
    guiParameters.showLightSources = true;
    EXPECT_TRUE(guiParameters.showLightSources);

    guiParameters.showLightSources = false;
    EXPECT_FALSE(guiParameters.showLightSources);
}

TEST_F(GuiParametersTest, CanSetAndGetSsaoParameters)
{
    guiParameters.ssaoKernelSize = 64;
    guiParameters.ssaoNoiseSize = 4;
    guiParameters.ssaoRadius = 0.5f;
    guiParameters.ssaoBias = 0.025f;
    guiParameters.enableSsao = true;

    EXPECT_EQ(guiParameters.ssaoKernelSize, 64u);
    EXPECT_EQ(guiParameters.ssaoNoiseSize, 4u);
    EXPECT_FLOAT_EQ(guiParameters.ssaoRadius, 0.5f);
    EXPECT_FLOAT_EQ(guiParameters.ssaoBias, 0.025f);
    EXPECT_TRUE(guiParameters.enableSsao);
}

TEST_F(GuiParametersTest, CanSetAndGetTrackballParameters)
{
    guiParameters.trackballInvertYAxis = true;
    guiParameters.trackballSensitivity = 0.5f;

    EXPECT_TRUE(guiParameters.trackballInvertYAxis);
    EXPECT_FLOAT_EQ(guiParameters.trackballSensitivity, 0.5f);
}

TEST_F(GuiParametersTest, CanSetAndGetRaycastingDensityMultiplier)
{
    guiParameters.raycastingDensityMultiplier = 2.0f;

    EXPECT_FLOAT_EQ(guiParameters.raycastingDensityMultiplier, 2.0f);
}

TEST_F(GuiParametersTest, CanAddPointLights)
{
    PointLight light1;
    light1.position = glm::vec3{1.0f, 2.0f, 3.0f};
    light1.ambient = glm::vec3{0.1f, 0.1f, 0.1f};

    PointLight light2;
    light2.position = glm::vec3{4.0f, 5.0f, 6.0f};
    light2.diffuse = glm::vec3{0.8f, 0.8f, 0.8f};

    guiParameters.pointLights.push_back(light1);
    guiParameters.pointLights.push_back(light2);

    EXPECT_EQ(guiParameters.pointLights.size(), 2u);
    EXPECT_EQ(guiParameters.pointLights[0].position, glm::vec3(1.0f, 2.0f, 3.0f));
    EXPECT_EQ(guiParameters.pointLights[1].position, glm::vec3(4.0f, 5.0f, 6.0f));
}

TEST_F(GuiParametersTest, CanSetDirectionalLight)
{
    guiParameters.directionalLight.direction = glm::vec3{0.0f, -1.0f, 0.0f};
    guiParameters.directionalLight.ambient = glm::vec3{0.2f, 0.2f, 0.2f};
    guiParameters.directionalLight.diffuse = glm::vec3{0.5f, 0.5f, 0.5f};
    guiParameters.directionalLight.specular = glm::vec3{1.0f, 1.0f, 1.0f};

    EXPECT_EQ(guiParameters.directionalLight.direction, glm::vec3(0.0f, -1.0f, 0.0f));
    EXPECT_EQ(guiParameters.directionalLight.ambient, glm::vec3(0.2f, 0.2f, 0.2f));
    EXPECT_EQ(guiParameters.directionalLight.diffuse, glm::vec3(0.5f, 0.5f, 0.5f));
    EXPECT_EQ(guiParameters.directionalLight.specular, glm::vec3(1.0f, 1.0f, 1.0f));
}
