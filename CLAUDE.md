# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

Veda is an OpenGL-based volume rendering demo that implements Screen Space Ambient Occlusion (SSAO) with shadow mapping. It uses modern C++ (C++26), CMake for build management, and leverages GLFW for windowing, GLAD for OpenGL loading, GLM for mathematics, and ImGui for the GUI.

## Build System

### Dependencies
- CMake 3.10+
- C++26 compiler (MSVC recommended on Windows)
- vcpkg (packages installed at `C:/Libraries/vcpkg/installed/x64-windows`)
- Required libraries: GLM, GLFW3, OpenGL

### Build Commands
```bash
# Configure and build (from project root)
cmake -B build
cmake --build build

# The executable will be in build/src/Debug/veda.exe (Debug) or build/src/Release/veda.exe (Release)
```

### Important CMake Details
- Root `CMakeLists.txt` configures C++26 standard, MSVC runtime library settings, and generates `cmake/root_directory.h` for path resolution
- GLAD is built as a static library from source in `lib/glad/`
- GLM and GLFW3 are located via vcpkg
- Shader files (`.vert`, `.geom`, `.frag`) are included in the build for IDE organization

## Code Architecture

### Source Organization
The codebase follows a modular structure under `src/`:

- **buffers/**: OpenGL buffer abstractions (FrameBuffer, VertexBuffer)
- **camera/**: Camera system for 3D navigation
- **config/**: Global configuration (window size, shadow map resolution, SSAO parameters, lighting defaults)
- **context/**: OpenGL initialization (GLFW window creation, GLAD loading, GL state setup)
- **gui/**: ImGui integration for runtime parameter adjustment
- **imgui/**: ImGui library source files
- **input/**: Input handling and display properties
- **lights/**: Lighting system (DirectionalLight, PointLight) with factory functions
- **shaders/**: GLSL shader files for rendering pipeline stages
- **textures/**: Texture wrapper and texture unit management
- **utils/**: Shader loading, SSAO utilities, file system helpers

### Rendering Pipeline
The application implements a multi-pass deferred rendering pipeline (see `Main.cpp`):

1. **Shadow Map Pass**: Renders scene from light's perspective into depth buffer (shadowFrameBuffer)
2. **SSAO Input Pass**: Renders geometry into G-buffer (position, light-space position, normals, albedo, point light contribution, stencil)
3. **SSAO Pass**: Computes ambient occlusion from G-buffer data using randomized kernel samples
4. **SSAO Blur Pass**: Applies blur to reduce noise in SSAO output
5. **SSAO Compositing Pass**: Combines all buffers with lighting calculations to produce final image
6. **Forward Pass**: Renders light source visualizations and debug overlays

### Key Components

**Config System** (`config/Config.h`):
- Centralized configuration namespace with compile-time constants
- Window dimensions, shadow map resolution, SSAO parameters
- Default lighting setup via factory functions

**Shader Management** (`utils/Shader.h`):
- Shader compilation and linking
- Uniform setting helpers
- Paths resolved via `FileSystem::getPath()` using generated `root_directory.h`

**Texture System** (`textures/Texture.h`):
- Encapsulates OpenGL texture creation and binding
- Supports various internal formats (depth, color, HDR)
- Texture unit mapping managed separately

**FrameBuffer Abstraction** (`buffers/FrameBuffer.h`):
- Simplifies FBO creation and attachment
- Used for shadow maps, G-buffer, SSAO intermediate buffers

**Input Handling** (`input/InputHandler.h`):
- Processes keyboard/mouse input
- Updates camera based on user interaction
- Manages display properties (GUI visibility, debug views)

**GUI System** (`gui/Gui.h`):
- ImGui-based interface for tweaking lighting, SSAO parameters
- Updates `GuiParameters` which drive shader uniforms
- Sets `GuiUpdateFlags` to signal when expensive resources need regeneration (e.g., SSAO noise texture)

### Initialization Flow
1. `Context::InitGlfw()` - Create GLFW window
2. `Context::InitGlad()` - Load OpenGL function pointers
3. `Context::InitGl()` - Set up OpenGL state (blending, depth testing)
4. Load shaders from `src/shaders/` using `FileSystem::getPath()`
5. Create textures and framebuffers for multi-pass rendering
6. Initialize camera, input handler, GUI
7. Enter main render loop

### Conventions
- Headers use include guards (`#ifndef HEADER_H`)
- Factory functions prefixed with `Make` (e.g., `MakeGuiParameters()`, `MakeDefaultPointLights()`)
- OpenGL resources created in main loop (no RAII wrappers yet - see TODOs in `Main.cpp`)
- Shader uniforms updated per-frame or on GUI parameter changes
- Anonymous namespaces in `Main.cpp` for helper functions that should be refactored into separate modules (marked with `// TODO move` comments)

## Development Workflow

### Modifying Shaders
Shaders are loaded at runtime via `FileSystem::getPath("src/shaders/...")`. Changes to `.vert`, `.frag`, or `.geom` files require restarting the application (no hot reload).

### Adding New Rendering Features
1. Modify or add shaders in `src/shaders/`
2. Update `GuiParameters` if runtime tweaking is needed
3. Add corresponding GUI controls in `gui/Gui.cpp`
4. Update render passes in `Main.cpp` main loop
5. If new framebuffers/textures are needed, create them in initialization section

### Adjusting Lighting
- Default lights defined in `config/Config.h` via factory functions
- Runtime adjustments via GUI (stores in `GuiParameters`)
- Lighting parameters passed to shaders in `UpdateLightingParametersInShader()` helpers

### Camera Configuration
The camera is initialized with hardcoded position/orientation in `Main.cpp:259`. Modify these values or implement a camera preset system if different starting views are needed.
