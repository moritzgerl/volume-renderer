#include <gtest/gtest.h>

#include <camera/Camera.h>
#include <camera/CameraParameters.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class CameraTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        cameraParameters = CameraParameters
        {
            .position = glm::vec3{0.0f, 0.0f, 3.0f},
            .lookAt = glm::vec3{0.0f, 0.0f, 0.0f},
            .up = glm::vec3{0.0f, 1.0f, 0.0f},
            .zoom = 45.0f
        };

        camera = std::make_unique<Camera>(cameraParameters);
    }

    CameraParameters cameraParameters;
    std::unique_ptr<Camera> camera;
};

TEST_F(CameraTest, IsInitialPositionCorrect)
{
    EXPECT_EQ(camera->GetPosition(), cameraParameters.position);
}

TEST_F(CameraTest, IsInitialZoomCorrect)
{
    EXPECT_FLOAT_EQ(camera->GetZoom(), cameraParameters.zoom);
}

TEST_F(CameraTest, CanGetCameraParameters)
{
    const auto retrievedParams = camera->GetCameraParameters();

    EXPECT_EQ(retrievedParams.position, cameraParameters.position);
    EXPECT_EQ(retrievedParams.lookAt, cameraParameters.lookAt);
    EXPECT_EQ(retrievedParams.up, cameraParameters.up);
    EXPECT_FLOAT_EQ(retrievedParams.zoom, cameraParameters.zoom);
}

TEST_F(CameraTest, GetViewMatrixReturnsValidMatrix)
{
    const auto viewMatrix = camera->GetViewMatrix();

    // Verify it's not an identity matrix
    EXPECT_NE(viewMatrix, glm::mat4{1.0f});

    // Verify it matches expected lookAt matrix
    const auto expectedMatrix = glm::lookAt(
        cameraParameters.position,
        cameraParameters.lookAt,
        cameraParameters.up);

    // Compare matrices element by element with small tolerance
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            EXPECT_NEAR(viewMatrix[i][j], expectedMatrix[i][j], 0.0001f);
        }
    }
}

TEST_F(CameraTest, MouseScrollIncreasesZoom)
{
    // First decrease zoom from maximum
    camera->ProcessMouseScroll(10.0f);
    const float initialZoom = camera->GetZoom();
    const float scrollAmount = -5.0f; // Negative scroll increases zoom

    camera->ProcessMouseScroll(scrollAmount);

    EXPECT_GT(camera->GetZoom(), initialZoom);
}

TEST_F(CameraTest, MouseScrollDecreasesZoom)
{
    const float initialZoom = camera->GetZoom();
    const float scrollAmount = 5.0f; // Positive scroll decreases zoom

    camera->ProcessMouseScroll(scrollAmount);

    EXPECT_LT(camera->GetZoom(), initialZoom);
}

TEST_F(CameraTest, ZoomIsClampedToMinimum)
{
    // Scroll far enough to hit minimum
    camera->ProcessMouseScroll(100.0f);

    EXPECT_FLOAT_EQ(camera->GetZoom(), 1.0f);
}

TEST_F(CameraTest, ZoomIsClampedToMaximum)
{
    // Scroll far enough to hit maximum (default is 45.0f)
    camera->ProcessMouseScroll(-100.0f);

    EXPECT_FLOAT_EQ(camera->GetZoom(), 45.0f);
}

TEST_F(CameraTest, MouseMovementChangesPosition)
{
    const auto initialPosition = camera->GetPosition();

    camera->ProcessMouseMovement(0.1f, 0.0f, false, 1.0f);

    EXPECT_NE(camera->GetPosition(), initialPosition);
}

TEST_F(CameraTest, MouseMovementWithInvertYInvertsVerticalRotation)
{
    auto camera1 = Camera(cameraParameters);
    auto camera2 = Camera(cameraParameters);

    const float xOffset = 0.0f;
    const float yOffset = 0.1f;

    camera1.ProcessMouseMovement(xOffset, yOffset, false, 1.0f);
    camera2.ProcessMouseMovement(xOffset, yOffset, true, 1.0f);

    // The Y positions should be different when inverted
    EXPECT_NE(camera1.GetPosition().y, camera2.GetPosition().y);
}

TEST_F(CameraTest, SensitivityAffectsRotationAmount)
{
    auto camera1 = Camera(cameraParameters);
    auto camera2 = Camera(cameraParameters);

    const float xOffset = 0.1f;
    const float yOffset = 0.1f;

    camera1.ProcessMouseMovement(xOffset, yOffset, false, 1.0f);
    camera2.ProcessMouseMovement(xOffset, yOffset, false, 2.0f);

    // Higher sensitivity should result in larger position change
    const auto delta1 = glm::length(camera1.GetPosition() - cameraParameters.position);
    const auto delta2 = glm::length(camera2.GetPosition() - cameraParameters.position);

    EXPECT_GT(delta2, delta1);
}

TEST_F(CameraTest, CameraParametersRoundTrip)
{
    // Modify camera state
    camera->ProcessMouseScroll(-5.0f);
    camera->ProcessMouseMovement(0.1f, 0.1f, false, 1.0f);

    // Get parameters and create new camera
    const auto params = camera->GetCameraParameters();
    auto newCamera = Camera(params);

    // Verify state is preserved
    EXPECT_EQ(newCamera.GetPosition(), camera->GetPosition());
    EXPECT_FLOAT_EQ(newCamera.GetZoom(), camera->GetZoom());
}
