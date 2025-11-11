#include <persistence/SaveApplicationStateToIniFile.h>
#include <persistence/ApplicationStateIniFileSectionNames.h>
#include <camera/CameraParameters.h>
#include <config/Config.h>
#include <gui/GuiParameters.h>

#include <fstream>
#include <iomanip>

std::expected<void, Persistence::ApplicationStateIniFileSavingError> Persistence::SaveApplicationStateToIniFile(const ApplicationState& applicationState, const std::filesystem::path& iniFilePath)
{
    std::ofstream file(iniFilePath);
    if (!file.is_open())
    {
        return std::unexpected(ApplicationStateIniFileSavingError::CannotOpenFile);
    }

    const CameraParameters& cameraParameters = applicationState.cameraParameters;
    const GuiParameters& guiParameters = applicationState.guiParameters;

    file << std::fixed << std::setprecision(6);

    file << SectionNames::camera << "\n";
    file << "PositionX=" << cameraParameters.position.x << "\n";
    file << "PositionY=" << cameraParameters.position.y << "\n";
    file << "PositionZ=" << cameraParameters.position.z << "\n";
    // lookAt and world up of our orbit camera are constant in world space and thus not saved
    file << "Zoom=" << cameraParameters.zoom << "\n";
    file << "\n";

    file << SectionNames::guiParameters << "\n";

    // Transfer Function
    file << SectionNames::transferFunction << "\n";
    file << "\n";

    for (size_t i = 0; i < guiParameters.transferFunction.numActivePoints; ++i)
    {
        const auto& point = guiParameters.transferFunction.controlPoints[i];

        file << SectionNames::transferFunctionPointPrefix << i << "]\n";
        file << "Value=" << point.value << "\n";
        file << "ColorR=" << point.color.r << "\n";
        file << "ColorG=" << point.color.g << "\n";
        file << "ColorB=" << point.color.b << "\n";
        file << "Opacity=" << point.opacity << "\n";
        file << "\n";
    }

    // Trackball
    file << SectionNames::trackball << "\n";
    file << "TrackballInvertYAxis=" << (guiParameters.trackballInvertYAxis ? 1 : 0) << "\n";
    file << "TrackballSensitivity=" << guiParameters.trackballSensitivity << "\n";
    file << "\n";

    // SSAO
    file << SectionNames::ssao << "\n";
    file << "SsaoKernelSize=" << guiParameters.ssaoKernelSize << "\n";
    file << "SsaoNoiseSize=" << guiParameters.ssaoNoiseSize << "\n";
    file << "SsaoRadius=" << guiParameters.ssaoRadius << "\n";
    file << "SsaoBias=" << guiParameters.ssaoBias << "\n";
    file << "SsaoEnable=" << (guiParameters.enableSsao ? 1 : 0) << "\n";
    file << "\n";

    // Directional Light
    file << SectionNames::directionalLight << "\n";
    file << "DirectionX=" << guiParameters.directionalLight.direction.x << "\n";
    file << "DirectionY=" << guiParameters.directionalLight.direction.y << "\n";
    file << "DirectionZ=" << guiParameters.directionalLight.direction.z << "\n";
    file << "AmbientR=" << guiParameters.directionalLight.ambient.r << "\n";
    file << "AmbientG=" << guiParameters.directionalLight.ambient.g << "\n";
    file << "AmbientB=" << guiParameters.directionalLight.ambient.b << "\n";
    file << "DiffuseR=" << guiParameters.directionalLight.diffuse.r << "\n";
    file << "DiffuseG=" << guiParameters.directionalLight.diffuse.g << "\n";
    file << "DiffuseB=" << guiParameters.directionalLight.diffuse.b << "\n";
    file << "SpecularR=" << guiParameters.directionalLight.specular.r << "\n";
    file << "SpecularG=" << guiParameters.directionalLight.specular.g << "\n";
    file << "SpecularB=" << guiParameters.directionalLight.specular.b << "\n";
    file << "Intensity=" << guiParameters.directionalLight.intensity << "\n";
    file << "\n";

    // Point Lights
    for (unsigned int i = 0; i < Config::numPointLights; ++i)
    {
        const auto& pointLight = guiParameters.pointLights[i];

        file << SectionNames::pointLightPrefix << i << "]\n";
        file << "PositionX=" << pointLight.position.x << "\n";
        file << "PositionY=" << pointLight.position.y << "\n";
        file << "PositionZ=" << pointLight.position.z << "\n";
        file << "AmbientR=" << pointLight.ambient.r << "\n";
        file << "AmbientG=" << pointLight.ambient.g << "\n";
        file << "AmbientB=" << pointLight.ambient.b << "\n";
        file << "DiffuseR=" << pointLight.diffuse.r << "\n";
        file << "DiffuseG=" << pointLight.diffuse.g << "\n";
        file << "DiffuseB=" << pointLight.diffuse.b << "\n";
        file << "SpecularR=" << pointLight.specular.r << "\n";
        file << "SpecularG=" << pointLight.specular.g << "\n";
        file << "SpecularB=" << pointLight.specular.b << "\n";
        file << "Intensity=" << pointLight.intensity << "\n";
        file << "\n";
    }

    // Rendering
    file << SectionNames::rendering << "\n";
    file << "ShowLightSources=" << (guiParameters.showLightSources ? 1 : 0) << "\n";
    file << "DensityMultiplier=" << guiParameters.raycastingDensityMultiplier << "\n";
    file << "\n";

    if (!file.good())
    {
        return std::unexpected(ApplicationStateIniFileSavingError::WriteError);
    }

    return {};
}
