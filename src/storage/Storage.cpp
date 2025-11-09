#include <storage/Storage.h>
#include <config/Config.h>
#include <data/PersistSaveStateToIni.h>

Storage::Storage(
    Camera&& camera,
    DisplayProperties&& displayProperties,
    GuiParameters&& guiParameters,
    GuiUpdateFlags&& guiUpdateFlags,
    ScreenQuad&& screenQuad,
    SsaoUtils&& ssaoUtils,
    TextureStorage&& textureStorage,
    ShaderStorage&& shaderStorage,
    FrameBufferStorage&& frameBufferStorage,
    UnitCube&& unitCube,
    Data::SaveState&& saveState,
    Data::VolumeData&& volumeData,
    Context::GlfwWindow&& window)
    : m_camera(std::move(camera))
    , m_displayProperties(std::move(displayProperties))
    , m_guiParameters(std::move(guiParameters))
    , m_guiUpdateFlags(std::move(guiUpdateFlags))
    , m_screenQuad(std::move(screenQuad))
    , m_unitCube(std::move(unitCube))
    , m_ssaoUtils(std::move(ssaoUtils))
    , m_textureStorage(std::move(textureStorage))
    , m_shaderStorage(std::move(shaderStorage))
    , m_frameBufferStorage(std::move(frameBufferStorage))
    , m_saveState(std::move(saveState))
    , m_volumeData(std::move(volumeData))
    , m_window(std::move(window))
{
}

Texture const& Storage::GetTexture(TextureId textureId) const
{
    return m_textureStorage.GetElement(textureId);
}

Texture& Storage::GetTexture(TextureId textureId)
{
    return m_textureStorage.GetElement(textureId);
}

Shader const& Storage::GetShader(ShaderId shaderId) const
{
    return m_shaderStorage.GetElement(shaderId);
}

const FrameBuffer& Storage::GetFrameBuffer(FrameBufferId frameBufferId) const
{
    return m_frameBufferStorage.GetElement(frameBufferId);
}

Camera& Storage::GetCamera()
{
    return m_camera;
}

const Camera& Storage::GetCamera() const
{
    return m_camera;
}

DisplayProperties& Storage::GetDisplayProperties()
{
    return m_displayProperties;
}

const DisplayProperties& Storage::GetDisplayProperties() const
{
    return m_displayProperties;
}

GuiParameters& Storage::GetGuiParameters()
{
    return m_guiParameters;
}

const GuiParameters& Storage::GetGuiParameters() const
{
    return m_guiParameters;
}

GuiUpdateFlags& Storage::GetGuiUpdateFlags()
{
    return m_guiUpdateFlags;
}

const GuiUpdateFlags& Storage::GetGuiUpdateFlags() const
{
    return m_guiUpdateFlags;
}

const ScreenQuad& Storage::GetScreenQuad() const
{
    return m_screenQuad;
}

const UnitCube& Storage::GetUnitCube() const
{
    return m_unitCube;
}

SsaoUtils& Storage::GetSsaoUtils()
{
    return m_ssaoUtils;
}

const SsaoUtils& Storage::GetSsaoUtils() const
{
    return m_ssaoUtils;
}

const TextureStorage& Storage::GetTextureStorage() const
{
    return m_textureStorage;
}

const ShaderStorage& Storage::GetShaderStorage() const
{
    return m_shaderStorage;
}

const FrameBufferStorage& Storage::GetFrameBufferStorage() const
{
    return m_frameBufferStorage;
}

Context::GlfwWindow& Storage::GetWindow()
{
    return m_window;
}

const Context::GlfwWindow& Storage::GetWindow() const
{
    return m_window;
}

Data::SaveState& Storage::GetSaveState()
{
    return m_saveState;
}

const Data::SaveState& Storage::GetSaveState() const
{
    return m_saveState;
}

const Data::VolumeData& Storage::GetVolumeData() const
{
    return m_volumeData;
}

void Storage::PersistSaveState() const
{
    Data::PersistSaveStateToIni(m_saveState, Config::saveStatePath);
}
