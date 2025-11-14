/**
* \file Storage.h
*
* \brief Central storage for application state and OpenGL resources.
*/

#ifndef STORAGE_H
#define STORAGE_H

#include <storage/StorageTypes.h>

#include <camera/Camera.h>
#include <context/GlfwWindow.h>
#include <gui/GuiParameters.h>
#include <gui/GuiUpdateFlags.h>
#include <input/DisplayProperties.h>
#include <input/InputHandler.h>
#include <primitives/ScreenQuad.h>
#include <primitives/UnitCube.h>
#include <ssao/SsaoKernel.h>
#include <ssao/SsaoUpdater.h>
#include <volumedata/VolumeData.h>

#include <memory>
#include <vector>

/**
* \class Storage
*
* \brief Central owner of all application state and OpenGL resources.
*
* Owns all major components and resources including Camera, primitives, textures, shaders, framebuffers,
* volume data, and the GLFW window. All other application components work on references or pointers
* into the Storage rather than owning resources themselves.
*
* This centralized storage pattern simplifies resource management, ensures consistent lifetimes,
* and provides a single point of access for all application state.
*
* The resources are passed into the constructor as rvalue references and moved into the Storage.
* Storage is non-copyable and non-movable to ensure single ownership.
*
* @see Factory::MakeStorage for construction of the storage with all components.
* @see InputHandler for accessing storage resources for input handling.
* @see Gui for accessing storage resources for GUI rendering.
* @see SsaoUpdater for updating SSAO textures in the storage.
* @see TransferFunctionTextureUpdater for updating transfer function textures in the storage.
* @see RenderPass for accessing storage resources during rendering.
*/
class Storage
{
public:
    /**
    * Constructor.
    * @param camera The camera as rvalue reference to be moved into the storage.
    * @param displayProperties The display properties as rvalue reference to be moved into the storage.
    * @param guiParameters The GUI parameters as rvalue reference to be moved into the storage.
    * @param guiUpdateFlags The GUI update flags as rvalue reference to be moved into the storage.
    * @param screenQuad The screen quad primitive as rvalue reference to be moved into the storage.
    * @param ssaoKernel The SSAO kernel as rvalue reference to be moved into the storage.
    * @param textureStorage The texture storage as rvalue reference to be moved into the storage.
    * @param shaderStorage The shader storage as rvalue reference to be moved into the storage.
    * @param frameBufferStorage The framebuffer storage as rvalue reference to be moved into the storage.
    * @param unitCube The unit cube primitive as rvalue reference to be moved into the storage.
    * @param volumeData The volume data as rvalue reference to be moved into the storage.
    * @param window The GLFW window as rvalue reference to be moved into the storage.
    */
    explicit Storage(
        Camera&& camera,
        DisplayProperties&& displayProperties,
        GuiParameters&& guiParameters,
        GuiUpdateFlags&& guiUpdateFlags,
        ScreenQuad&& screenQuad,
        SsaoKernel&& ssaoKernel,
        TextureStorage&& textureStorage,
        ShaderStorage&& shaderStorage,
        FrameBufferStorage&& frameBufferStorage,
        UnitCube&& unitCube,
        VolumeData::VolumeData&& volumeData,
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
    SsaoKernel& GetSsaoKernel();
    const SsaoKernel& GetSsaoKernel() const;

    /**
    * Retrieves a texture by ID.
    * @param textureId The ID of the texture to retrieve.
    * @return const Texture& The requested texture.
    */
    Texture const& GetTexture(TextureId textureId) const;
    Texture& GetTexture(TextureId textureId);

    /**
    * Retrieves a shader by ID.
    * @param shaderId The ID of the shader to retrieve.
    * @return const Shader& The requested shader.
    */
    Shader const& GetShader(ShaderId shaderId) const;

    /**
    * Retrieves a framebuffer by ID.
    * @param frameBufferId The ID of the framebuffer to retrieve.
    * @return const FrameBuffer& The requested framebuffer.
    */
    const FrameBuffer& GetFrameBuffer(FrameBufferId frameBufferId) const;
    const TextureStorage& GetTextureStorage() const;
    const ShaderStorage& GetShaderStorage() const;
    const FrameBufferStorage& GetFrameBufferStorage() const;
    Context::GlfwWindow& GetWindow();
    const Context::GlfwWindow& GetWindow() const;
    const VolumeData::VolumeData& GetVolumeData() const;

    /**
    * Saves the application state to an INI file.
    * Persists camera parameters, GUI parameters, and transfer function control points.
    * @return void
    */
    void SaveApplicationState() const;

private:
    Camera m_camera; /**< Camera for 3D navigation and view transformation. */
    DisplayProperties m_displayProperties; /**< Display properties for window state and GUI visibility. */
    GuiParameters m_guiParameters; /**< GUI parameters for lighting, SSAO, and transfer function settings. */
    GuiUpdateFlags m_guiUpdateFlags; /**< Flags indicating when expensive resources need regeneration. */
    ScreenQuad m_screenQuad; /**< Screen-aligned quad for full-screen rendering passes. */
    UnitCube m_unitCube; /**< Unit cube for volume ray-casting entry/exit point generation. */
    SsaoKernel m_ssaoKernel; /**< SSAO sample kernel for ambient occlusion computation. */
    TextureStorage m_textureStorage; /**< Storage for all OpenGL textures indexed by TextureId. */
    ShaderStorage m_shaderStorage; /**< Storage for all shader programs indexed by ShaderId. */
    FrameBufferStorage m_frameBufferStorage; /**< Storage for all framebuffers indexed by FrameBufferId. */
    VolumeData::VolumeData m_volumeData; /**< 3D volume data with metadata (dimensions, bit depth). */
    Context::GlfwWindow m_window; /**< GLFW window with custom deleter for OpenGL context. */
};

#endif
