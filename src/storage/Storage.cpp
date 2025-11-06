#include <storage/Storage.h>

Storage::Storage(
    Camera&& camera,
    DisplayProperties&& displayProperties,
    Gui&& gui,
    GuiParameters&& guiParameters,
    GuiUpdateFlags&& guiUpdateFlags,
    InputHandler&& inputHandler,
    ScreenQuad&& screenQuad,
    SsaoUpdater&& ssaoUpdater,
    SsaoUtils&& ssaoUtils,
    TextureStorage&& textureStorage,
    ShaderStorage&& shaderStorage,
    FrameBufferStorage&& frameBufferStorage,
    RenderPassStorage&& renderPassStorage,
    UnitCube&& unitCube,
    Data::VolumeData&& volumeData,
    Context::GlfwWindow&& window)
    : m_camera(std::move(camera))
    , m_displayProperties(std::move(displayProperties))
    , m_gui(std::move(gui))
    , m_guiParameters(std::move(guiParameters))
    , m_guiUpdateFlags(std::move(guiUpdateFlags))
    , m_inputHandler(std::move(inputHandler))
    , m_screenQuad(std::move(screenQuad))
    , m_ssaoUpdater(std::move(ssaoUpdater))
    , m_ssaoUtils(std::move(ssaoUtils))
    , m_textureStorage(std::move(textureStorage))
    , m_shaderStorage(std::move(shaderStorage))
    , m_frameBufferStorage(std::move(frameBufferStorage))
    , m_renderPassStorage(std::move(renderPassStorage))
    , m_unitCube(std::move(unitCube))
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

const RenderPass& Storage::GetRenderPass(RenderPassId renderPassId) const
{
    return m_renderPassStorage.GetElement(renderPassId);
}

const std::vector<RenderPass>& Storage::GetRenderPasses() const
{
    return m_renderPassStorage.GetElements();
}

const DisplayProperties& Storage::GetDisplayProperties() const
{
    return m_displayProperties;
}

Gui& Storage::GetGui()
{
    return m_gui;
}

InputHandler& Storage::GetInputHandler()
{
    return m_inputHandler;
}

SsaoUpdater& Storage::GetSsaoUpdater()
{
    return m_ssaoUpdater;
}

Context::GlfwWindow& Storage::GetWindow()
{
    return m_window;
}

const Data::VolumeData& Storage::GetVolumeData() const
{
    return m_volumeData;
}
