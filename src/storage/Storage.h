#ifndef STORAGE_H
#define STORAGE_H

#include <storage/StorageTypes.h>
#include <camera/Camera.h>
#include <context/GlfwWindow.h>
#include <data/VolumeData.h>
#include <gui/Gui.h>
#include <gui/GuiParameters.h>
#include <gui/GuiUpdateFlags.h>
#include <input/DisplayProperties.h>
#include <input/InputHandler.h>
#include <primitives/ScreenQuad.h>
#include <primitives/UnitCube.h>
#include <shader/SsaoUpdater.h>
#include <utils/SsaoUtils.h>

#include <memory>
#include <vector>

class Storage
{
public:
    explicit Storage(
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
        Context::GlfwWindow&& window);

    // TODO use concepts
    // TODO rule of zero? Don't even do the = delete here?
    // If we keep it, do the same in the other storage classes
    Storage(const Storage&) = delete;
    Storage& operator=(const Storage&) = delete;
    Storage(Storage&&) = delete;
    Storage& operator=(Storage&&) = delete;

    // TODO remove unused getters
    const DisplayProperties& GetDisplayProperties() const;
    Gui& GetGui();
    InputHandler& GetInputHandler();
    SsaoUpdater& GetSsaoUpdater();
    Texture const& GetTexture(TextureId textureId) const;
    Texture& GetTexture(TextureId textureId);
    Shader const& GetShader(ShaderId shaderId) const;
    const FrameBuffer& GetFrameBuffer(FrameBufferId frameBufferId) const;
    const RenderPass& GetRenderPass(RenderPassId renderPassId) const;
    const std::vector<RenderPass>& GetRenderPasses() const;
    Context::GlfwWindow& GetWindow();
    const Data::VolumeData& GetVolumeData() const;

private:
    Camera m_camera;
    DisplayProperties m_displayProperties;
    Gui m_gui;
    GuiParameters m_guiParameters;
    GuiUpdateFlags m_guiUpdateFlags;
    InputHandler m_inputHandler;
    ScreenQuad m_screenQuad;
    UnitCube m_unitCube;
    SsaoUpdater m_ssaoUpdater;
    SsaoUtils m_ssaoUtils;
    TextureStorage m_textureStorage;
    ShaderStorage m_shaderStorage;
    FrameBufferStorage m_frameBufferStorage;
    RenderPassStorage m_renderPassStorage;
    Data::VolumeData m_volumeData;
    Context::GlfwWindow m_window;
};

#endif
