#ifndef STORAGE_H
#define STORAGE_H

#include <storage/StorageTypes.h>
#include <camera/Camera.h>
#include <context/GlfwWindow.h>
#include <data/SaveState.h>
#include <data/VolumeData.h>
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
        Context::GlfwWindow&& window);

    // TODO use concepts
    // TODO rule of zero? Don't even do the = delete here?
    // If we keep it, do the same in the other storage classes
    Storage(const Storage&) = delete;
    Storage& operator=(const Storage&) = delete;
    Storage(Storage&&) = delete;
    Storage& operator=(Storage&&) = delete;

    // TODO remove unused getters
    Camera& GetCamera();
    const Camera& GetCamera() const;
    DisplayProperties& GetDisplayProperties();
    const DisplayProperties& GetDisplayProperties() const;
    GuiParameters& GetGuiParameters();
    const GuiParameters& GetGuiParameters() const;
    GuiUpdateFlags& GetGuiUpdateFlags();
    const GuiUpdateFlags& GetGuiUpdateFlags() const;
    const ScreenQuad& GetScreenQuad() const;
    const UnitCube& GetUnitCube() const;
    SsaoUtils& GetSsaoUtils();
    const SsaoUtils& GetSsaoUtils() const;
    Texture const& GetTexture(TextureId textureId) const;
    Texture& GetTexture(TextureId textureId);
    Shader const& GetShader(ShaderId shaderId) const;
    const FrameBuffer& GetFrameBuffer(FrameBufferId frameBufferId) const;
    const TextureStorage& GetTextureStorage() const;
    const ShaderStorage& GetShaderStorage() const;
    const FrameBufferStorage& GetFrameBufferStorage() const;
    Context::GlfwWindow& GetWindow();
    const Context::GlfwWindow& GetWindow() const;
    Data::SaveState& GetSaveState();
    const Data::SaveState& GetSaveState() const;
    const Data::VolumeData& GetVolumeData() const;

private:
    Camera m_camera;
    DisplayProperties m_displayProperties;
    GuiParameters m_guiParameters;
    GuiUpdateFlags m_guiUpdateFlags;
    ScreenQuad m_screenQuad;
    UnitCube m_unitCube;
    SsaoUtils m_ssaoUtils;
    TextureStorage m_textureStorage;
    ShaderStorage m_shaderStorage;
    FrameBufferStorage m_frameBufferStorage;
    Data::SaveState m_saveState;
    Data::VolumeData m_volumeData;
    Context::GlfwWindow m_window;
};

#endif
