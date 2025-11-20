# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

volume-renderer is an OpenGL-based volume rendering application that uses ray-casting with transfer functions to visualize 3D volumetric data. It implements Screen Space Ambient Occlusion (SSAO) for enhanced depth perception (not fully implemented yet). The application uses modern C++ (C++26), CMake for build management, and leverages GLFW for windowing, GLAD for OpenGL loading, GLM for mathematics, and ImGui for the GUI. It features an interactive transfer function editor, application state persistence, and a modular architecture built around a centralized storage pattern.

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

# The executable will be in build/src/Debug/VolumeRenderer.exe (Debug) or build/src/Release/VolumeRenderer.exe (Release)
```

### Important CMake Details
- Root `CMakeLists.txt` configures C++26 standard, MSVC runtime library settings, and generates `cmake/root_directory.h` for path resolution
- GLAD is built as a static library from source in `lib/glad/`
- GLM and GLFW3 are located via vcpkg
- Shader files (`.vert`, `.geom`, `.frag`) are included in the build for IDE organization

## Testing

### Test Organization
The project uses Google Test (GTest) for unit testing. Tests are organized in the `test/` directory, mirroring the structure of `src/`:

- **One test file per class** - Each class being tested should have its own dedicated test file
  - Example: `GuiParameters` class → `test/gui/gui_parameters_test.cpp`
  - Example: `GuiUpdateFlags` class → `test/gui/gui_update_flags_test.cpp`
  - Example: `Camera` class → `test/camera/camera_test.cpp`

- **Test file naming convention** - Use lowercase with underscores: `<class_name>_test.cpp`
  - Convert CamelCase class names to snake_case for test files
  - Always append `_test.cpp` suffix

- **Test fixtures** - Each test file should define a test fixture class inheriting from `::testing::Test`
  ```cpp
  class GuiParametersTest : public ::testing::Test
  {
  protected:
      void SetUp() override
      {
          guiParameters = GuiParameters{};
      }

      GuiParameters guiParameters;
  };
  ```

- **OpenGL context requirements** - Tests that use OpenGL functionality require context initialization:
  ```cpp
  void SetUp() override
  {
      window = std::make_unique<Context::GlfwWindow>();
      Context::InitGl();
      // ... create objects requiring OpenGL
  }
  ```

### Running Tests
```bash
# Build tests (included in normal build)
cmake --build build

# Run tests from install directory
./bin/test/VolumeRendererTest.exe

# Or run via CTest from build directory
cd build
ctest
```

### Test Coverage Guidelines
- Focus on testing class behavior and public API, not factory functions (which are integration code)
- Pure logic tests (like Camera) run very fast and don't require OpenGL
- OpenGL-dependent tests (like FrameBuffer, VertexBuffer) need context initialization
- Data structure tests (like GuiParameters, GuiUpdateFlags) verify state storage/retrieval

## Code Architecture

### Source Organization
The codebase follows a modular structure under `src/`:

- **buffers/**: OpenGL buffer abstractions (FrameBuffer, VertexBuffer) and factory functions for creating framebuffers
- **camera/**: Camera system for 3D navigation with CameraParameters for serialization
- **config/**: Global configuration (window size, transfer function constants)
- **context/**: OpenGL initialization (GLFW window creation with custom deleter, GLAD loading, GL state setup)
- **gui/**: ImGui integration for runtime parameter adjustment with modular widget creation (MakeSlider, MakeCheckbox) and transfer function editing
- **imgui/**: ImGui library source files
- **input/**: Input handling and display properties
- **lights/**: Lighting system (DirectionalLight, PointLight) with factory functions
- **persistence/**: Application state serialization/deserialization to/from INI files (camera, GUI parameters, transfer function)
- **primitives/**: Geometric primitives (ScreenQuad, UnitCube) with vertex coordinate data and rendering methods
- **renderpass/**: Render pass abstraction with RenderPassId enum and factory functions
- **shader/**: Shader compilation, linking, and uniform updating helpers (camera matrices, lighting parameters)
- **shaders/**: GLSL shader files for rendering pipeline stages
- **ssao/**: SSAO kernel generation and updater for managing SSAO texture resources
- **storage/**: Central storage system managing all application state and resources
- **textures/**: Texture wrapper, texture unit mapping, and factory functions for creating textures
- **transferfunction/**: Transfer function for volume rendering with control points, interpolation, and texture updating
- **utils/**: File system helpers for shader path resolution
- **volumedata/**: Volume data loading (raw format), metadata parsing, and 3D texture creation

### Application Architecture

The application uses a **centralized storage pattern** where all major components and resources are owned by the `Storage` class:

**Storage System** ([storage/Storage.h](src/storage/Storage.h)):
- Central owner of all application state and OpenGL resources
- Contains: Camera, DisplayProperties, GuiParameters, GuiUpdateFlags, primitives (ScreenQuad, UnitCube), SSAO kernel, textures, shaders, framebuffers, volume data, and GLFW window
- Provides getter methods for accessing stored components
- Handles application state persistence via `SaveApplicationState()`
- Initialized via `Factory::MakeStorage()` which constructs all components in the correct order

**Render Pass System** ([renderpass/RenderPass.h](src/renderpass/RenderPass.h)):
- Encapsulates each rendering stage as a self-contained object
- Each RenderPass contains: shader reference, framebuffer reference, texture references, prepare function (for GL state setup), and render function (for drawing commands)
- RenderPassId enum defines pipeline stages: Setup, Volume, SsaoInput, Ssao, SsaoBlur, SsaoFinal, LightSource, Debug
- Created via `Factory::MakeRenderPasses()` which configures the entire rendering pipeline
- Render passes are executed sequentially in the main loop

**Persistence System** ([persistence/](src/persistence/)):
- ApplicationState struct holds camera parameters, GUI parameters, and transfer function data
- LoadApplicationStateFromIniFile/SaveApplicationStateToIniFile handle serialization
- Custom parsers for each parameter type (ParseCameraParameter, ParseGuiParameter, ParseTransferFunctionControlPoint)
- Application state is loaded at startup and saved on shutdown

**Transfer Function System** ([transferfunction/](src/transferfunction/)):
- TransferFunction class manages control points for mapping scalar values to colors/opacity
- InterpolateTransferFunction performs interpolation between control points
- TransferFunctionTextureUpdater updates the 1D texture when control points change
- GUI provides interactive editing of control points

**Volume Rendering** ([volumedata/](src/volumedata/)):
- VolumeData class stores 3D volume data with metadata (dimensions, bit depth)
- LoadVolumeRaw reads raw volume files with accompanying metadata
- MakeVolumeDataTexture creates 3D OpenGL textures from volume data
- Volume rendering performed via ray-casting in fragment shader

### Rendering Pipeline
The application implements a multi-pass volume rendering pipeline with SSAO (see [Main.cpp](src/Main.cpp)):

1. **Setup Pass**: Clears the screen and prepares for rendering
2. **Volume Pass**: Ray-casts through the volume using transfer function to produce colored output
3. **SSAO Input Pass**: Renders geometry into G-buffer (position, normals, etc.) for SSAO computation
4. **SSAO Pass**: Computes ambient occlusion from G-buffer data using randomized kernel samples
5. **SSAO Blur Pass**: Applies blur to reduce noise in SSAO output
6. **SSAO Final Pass**: Combines volume rendering with SSAO to produce final composited image
7. **Light Source Pass**: Renders light source visualizations (if enabled)
8. **Debug Pass**: Renders debug overlays (if enabled)

### Key Components

**Config System** ([config/Config.h](src/config/Config.h)):
- Centralized configuration namespace with compile-time constants
- Window dimensions, transfer function constants (max control points)

**Shader Management** ([shader/Shader.h](src/shader/Shader.h)):
- Shader compilation and linking with error reporting
- Uniform setting helpers (int, float, vec3, mat4, etc.)
- Paths resolved via `FileSystem::getPath()` using generated `root_directory.h`
- Factory function `MakeShaders()` creates all shaders and stores them by ShaderId

**Texture System** ([textures/Texture.h](src/textures/Texture.h)):
- Encapsulates OpenGL texture creation and binding
- Supports various internal formats (depth, color, HDR, 3D volumes)
- TextureUnitMapping provides named binding points for shader samplers
- Factory function `MakeTextures()` creates all textures and stores them by TextureId

**FrameBuffer Abstraction** ([buffers/FrameBuffer.h](src/buffers/FrameBuffer.h)):
- Simplifies FBO creation and attachment management
- Stores framebuffer ID and dimensions
- Factory function `MakeFrameBuffers()` creates all framebuffers for the pipeline

**Input Handling** ([input/InputHandler.h](src/input/InputHandler.h)):
- Processes keyboard/mouse input via GLFW callbacks
- Updates camera based on user interaction
- Manages display properties (GUI visibility, debug views)
- Created via `Factory::MakeInputHandler()` with reference to Storage

**GUI System** ([gui/Gui.h](src/gui/Gui.h)):
- ImGui-based interface for tweaking lighting, SSAO, and transfer function parameters
- Updates `GuiParameters` which drive shader uniforms
- Sets `GuiUpdateFlags` to signal when expensive resources need regeneration (e.g., SSAO noise texture)
- TransferFunctionGui provides interactive control point editing
- Created via `Factory::MakeGui()` with reference to Storage

**SSAO Updater** ([ssao/SsaoUpdater.h](src/ssao/SsaoUpdater.h)):
- Monitors GuiUpdateFlags for changes requiring SSAO texture regeneration
- Regenerates SSAO kernel and noise textures when parameters change
- Updates textures in Storage via reference

**Transfer Function Texture Updater** ([transferfunction/TransferFunctionTextureUpdater.h](src/transferfunction/TransferFunctionTextureUpdater.h)):
- Monitors GuiUpdateFlags for transfer function changes
- Interpolates control points and updates 1D transfer function texture
- Updates texture in Storage via reference

### Main Loop Flow
The main loop in [Main.cpp](src/Main.cpp) is remarkably simple due to the refactored architecture:

1. **Initialization**: `Factory::MakeStorage()` creates Storage with all components (window, camera, textures, shaders, framebuffers, volume data)
2. **Create Components**: InputHandler, Gui, SsaoUpdater, TransferFunctionTextureUpdater created with Storage references
3. **Create Render Passes**: `Factory::MakeRenderPasses()` creates configured render pass sequence
4. **Main Loop**:
   - `inputHandler.Update()` - Process input and update camera
   - `ssaoUpdater.Update()` - Regenerate SSAO resources if needed
   - `transferFunctionTextureUpdater.Update()` - Update transfer function texture if needed
   - For each RenderPass: `renderPass.Render()` - Execute rendering stage
   - `gui.Draw()` - Render GUI
   - `window.PostRender()` - Swap buffers and poll events
5. **Shutdown**: Save application state and clean up GLFW

### Conventions
- Headers use include guards with underscores separating words (e.g., `#ifndef VOLUME_DATA_H`)
  - Insert underscores before each uppercase letter that follows a lowercase letter in CamelCase names
  - Example: `VolumeData` → `VOLUME_DATA_H`, `VolumeLoaderRaw` → `VOLUME_LOADER_RAW_H`
- Member variables use `m_` prefix followed by camelCase (e.g., `m_width`, `m_bitsPerComponent`)
- Factory functions prefixed with `Make` and placed in `Factory` namespace (e.g., `Factory::MakeGuiParameters()`, `Factory::MakeDefaultPointLights()`)
- Enum classes used for type-safe identifiers (RenderPassId, ShaderId, TextureId, FrameBufferId)
- Components access shared state via references to Storage rather than owning resources
- Updater pattern used for components that monitor flags and perform conditional updates (SsaoUpdater, TransferFunctionTextureUpdater)

## Coding Guidelines

### File and Folder Naming Conventions
- **File names use CamelCase starting with a capital letter** - All source files (`.cpp`, `.h`) should be named using CamelCase with an initial capital letter
  - Examples: `VolumeData.h`, `VolumeData.cpp`, `FrameBufferTest.cpp`, `Main.cpp`
  - This applies to both source files in `src/` and test files in `test/`
- **Folder names use lowercase** - All directory names should be in lowercase  
  - Examples: `camera/`, `shader/`, `textures/`

### Include Directives
- **Always use angle bracket includes** (`<>`) for all project headers, never quoted includes (`""`)
  - Correct: `#include <context/GlfwWindow.h>`
  - Incorrect: `#include "GlfwWindow.h"`
- **Sort includes alphabetically** within each group, with one exception: headers from the current module's folder come first
  - Example: In `context/GlfwWindow.cpp`, include `<context/...>` headers before other project headers
- **Organize includes in two groups** separated by a blank line:
  1. Project-local headers (from `src/`)
  2. Standard library and third-party headers (STL, GLFW, GLM, etc.)
- **Skip the blank line** between groups if the file has fewer than 5 includes total
- **Third-party library code** (such as imgui) may use its own conventions and should not be modified

Example with 5+ includes:
```cpp
#include <context/GlfwWindow.h>
#include <context/InitGl.h>
#include <camera/Camera.h>
#include <config/Config.h>

#include <GLFW/glfw3.h>
#include <memory>
```

Example with fewer than 5 includes:
```cpp
#include <context/GlfwWindowDeleter.h>
#include <GLFW/glfw3.h>
```

### Formatting and Style
- **Curly brackets always on their own line** - Opening and closing braces for all blocks (functions, classes, namespaces, control structures) must be placed on separate lines
  ```cpp
  void Function()
  {
      if (condition)
      {
          // code
      }
  }
  ```
- **Prefer switch statements over if-else chains** - When comparing a single variable against multiple constant values, use `switch` statements instead of `if-else if` chains for better readability and maintainability
  ```cpp
  // Preferred
  switch (value)
  {
      case 1:
          // handle case 1
          break;
      case 2:
          // handle case 2
          break;
      default:
          // handle default
          break;
  }

  // Avoid
  if (value == 1)
  {
      // handle case 1
  }
  else if (value == 2)
  {
      // handle case 2
  }
  else
  {
      // handle default
  }
  ```
- **Namespace scoping differs between headers and implementation files**:
  - In `.h` files: Use scoped curly brackets with proper indentation for namespace content
    ```cpp
    namespace Data
    {
        class VolumeData
        {
            // class members indented
        };
    }
    ```
  - In `.cpp` files: Use `::` prefix for namespace qualification (no curly brackets)
    ```cpp
    void Data::VolumeData::Method()
    {
        // implementation
    }
    ```
- **Namespace closing comments** - Do not add comments after closing namespace braces, except for anonymous namespaces
  ```cpp
  namespace Data
  {
      // ...
  }  // Correct: no comment

  namespace
  {
      // ...
  } // anonymous namespace  - Correct: comment allowed for anonymous namespaces
  ```
- **No comments after include guards** - Do not add comments after `#endif` directives
  ```cpp
  #ifndef VOLUME_DATA_H
  #define VOLUME_DATA_H
  // ...
  #endif  // Correct: no comment
  ```

### Modern C++ Practices
This project embraces modern C++ idioms and best practices:

- **Leverage the Standard Library** - Use STL containers, algorithms, and utilities wherever applicable rather than reinventing functionality
  ```cpp
  // Preferred
  std::vector<float> values;
  std::ranges::sort(values);

  // Avoid
  float values[100];
  // manual sorting implementation
  ```

- **Prefer STL algorithms over raw loops** - Use `<algorithm>`, `<ranges>`, and related headers instead of manual iteration when possible
  ```cpp
  // Preferred
  auto it = std::ranges::find_if(items, [](const auto& item) { return item.isValid(); });

  // Avoid
  Item* found = nullptr;
  for (size_t i = 0; i < items.size(); ++i) {
      if (items[i].isValid()) {
          found = &items[i];
          break;
      }
  }
  ```

- **Use modern C++26 features** - Take advantage of ranges, views, spans, and other modern constructs
  ```cpp
  // Use std::span for non-owning array views
  void ProcessData(std::span<const uint8_t> data);

  // Use ranges for composable operations
  auto filtered = data | std::views::filter(predicate) | std::views::transform(mapper);
  ```

- **Prefer references over pointers for non-owning dependencies** - When a class needs access to another object but doesn't own it, use reference members with RAII constructors to establish the dependency at construction time
  ```cpp
  // Preferred - references with RAII constructor
  class TransferFunctionGui
  {
  public:
      TransferFunctionGui(TransferFunction& transferFunction, GuiUpdateFlags& guiUpdateFlags);
  private:
      TransferFunction& m_transferFunction;
      GuiUpdateFlags& m_guiUpdateFlags;
  };

  // Avoid - raw pointers for non-owning dependencies
  class TransferFunctionGui
  {
  private:
      TransferFunction* m_transferFunction{nullptr};  // Not recommended
      GuiUpdateFlags* m_guiUpdateFlags{nullptr};      // Not recommended
  };
  ```

- **Prefer smart pointers over raw pointers for ownership** - Use `std::unique_ptr` for exclusive ownership and `std::shared_ptr` for shared ownership when dynamic allocation is required
  ```cpp
  // Preferred
  std::unique_ptr<Texture> texture = std::make_unique<Texture>();

  // Avoid
  Texture* texture = new Texture();
  // ... manual delete required
  ```

- **Initialize members in constructor, not in header** - Always initialize member variables in the constructor initializer list (in the `.cpp` file) rather than using in-class initializers in the header file
  ```cpp
  // Preferred - initialization in .cpp file
  // TransferFunctionGui.h
  class TransferFunctionGui
  {
  private:
      int m_draggedPointIndex;
      float m_gradientHeight;
      ImVec2 m_plotSize;
  };

  // TransferFunctionGui.cpp
  TransferFunctionGui::TransferFunctionGui(TransferFunction& transferFunction, GuiUpdateFlags& guiUpdateFlags)
      : m_draggedPointIndex{ -1 }
      , m_gradientHeight{ 15.0f }
      , m_plotSize{ }
  {
  }

  // Avoid - in-class initializers in header
  class TransferFunctionGui
  {
  private:
      int m_draggedPointIndex{-1};
      float m_gradientHeight{15.0f};
      ImVec2 m_plotSize{};
  };
  ```

- **Use anonymous namespaces instead of static** - In `.cpp` files, place internal implementation details in anonymous namespaces rather than using the `static` keyword
  ```cpp
  // Preferred (.cpp file)
  namespace
  {
      void HelperFunction() { /* ... */ }
      constexpr int kConstant = 42;
  } // anonymous namespace

  // Avoid
  static void HelperFunction() { /* ... */ }
  static const int kConstant = 42;
  ```

- **Avoid classes without members** - If a class has no member variables and only static methods, use free functions in a namespace instead
  ```cpp
  // Preferred
  namespace MathUtils
  {
      float CalculateDistance(const glm::vec3& a, const glm::vec3& b);
  }

  // Avoid
  class MathUtils
  {
  public:
      static float CalculateDistance(const glm::vec3& a, const glm::vec3& b);
  };
  ```

- **Prefer uniform initialization** - Use brace initialization `{}` for consistency and to avoid narrowing conversions
  ```cpp
  // Preferred
  int count{0};
  std::vector<float> values{1.0f, 2.0f, 3.0f};
  Camera camera{position, target, up};

  // Acceptable for simple types
  int count = 0;
  ```

- **Apply const correctness rigorously** - Mark variables and member functions as `const` whenever they do not modify state, ensuring immutability is enforced at compile-time
  ```cpp
  // Preferred - const variables and const member functions
  std::optional<size_t> TransferFunctionGui::GetNearestPointIndex() const
  {
      auto calculateDistance = [&](size_t index)
      {
          const auto& point = m_transferFunction[index];
          const float x = m_plotPos.x + point.value * m_plotSize.x;
          const float y = m_plotPos.y + m_plotSize.y - m_gradientHeight - (point.opacity * m_interactiveAreaHeight);
          return std::sqrt((m_mousePos.x - x) * (m_mousePos.x - x) + (m_mousePos.y - y) * (m_mousePos.y - y));
      };
      // ...
  }

  // Avoid - missing const qualifiers
  std::optional<size_t> TransferFunctionGui::GetNearestPointIndex()  // Should be const
  {
      auto calculateDistance = [&](size_t index)
      {
          auto& point = m_transferFunction[index];  // Should be const auto&
          float x = m_plotPos.x + point.value * m_plotSize.x;  // Should be const float
          // ...
      };
      // ...
  }
  ```
  Guidelines for const correctness:
  - Mark member functions `const` if they do not modify member variables
  - Use `const auto&` for local variables that reference objects and won't be modified
  - Use `const` for local variables that won't be reassigned (especially in tight scopes like lambdas)
  - Prefer `const` references for function parameters that won't be modified

- **Follow core design principles**:
  - **RAII (Resource Acquisition Is Initialization)**: Manage resources through object lifetimes; acquire in constructor, release in destructor
  - **YAGNI (You Aren't Gonna Need It)**: Don't implement functionality until it's actually needed
  - **KISS (Keep It Simple, Stupid)**: Favor simple, straightforward solutions over complex ones
  - **DRY (Don't Repeat Yourself)**: Extract common functionality into reusable functions or classes; use factory functions for repeated object construction patterns

## Development Workflow

### Modifying Shaders
Shaders are loaded at runtime via `FileSystem::getPath("src/shaders/...")`. Changes to `.vert` or `.frag` files require restarting the application (no hot reload).

### Adding New Rendering Features
1. Modify or add shaders in `src/shaders/`
2. Update `GuiParameters` if runtime tweaking is needed
3. Add corresponding GUI controls in `gui/Gui.cpp` or `gui/TransferFunctionGui.cpp`
4. Add new RenderPassId to [renderpass/RenderPassId.h](src/renderpass/RenderPassId.h) if needed
5. Update `Factory::MakeRenderPasses()` in [renderpass/MakeRenderPasses.cpp](src/renderpass/MakeRenderPasses.cpp) to include new pass
6. If new framebuffers/textures are needed:
   - Add TextureId/FrameBufferId enums to respective header files
   - Update factory functions in [textures/MakeTextures.cpp](src/textures/MakeTextures.cpp) or [buffers/MakeFrameBuffers.cpp](src/buffers/MakeFrameBuffers.cpp)

### Adjusting Lighting
- Default lights defined via factory functions in [lights/](src/lights/)
- Runtime adjustments via GUI (stores in `GuiParameters`)
- Lighting parameters passed to shaders via `UpdateLightingParametersInShader()` in [shader/UpdateLightingParametersInShader.cpp](src/shader/UpdateLightingParametersInShader.cpp)

### Modifying Transfer Functions
- Default transfer function defined in [transferfunction/MakeDefaultTransferFunction.cpp](src/transferfunction/MakeDefaultTransferFunction.cpp)
- Interactive editing via GUI using TransferFunctionGui
- Transfer function stored as control points in GuiParameters
- TransferFunctionTextureUpdater automatically updates the 1D texture when control points change
- Interpolation performed by InterpolateTransferFunction

### Camera Configuration
- Default camera parameters created in [camera/MakeDefaultCameraParameters.cpp](src/camera/MakeDefaultCameraParameters.cpp)
- Camera state persisted to/loaded from INI file via persistence system
- Runtime control via mouse/keyboard through InputHandler

### Application State Persistence
- Application state (camera, GUI parameters, transfer function) automatically saved to `settings.ini` on shutdown
- State loaded from `settings.ini` on startup if file exists
- To modify persistence behavior, edit [persistence/SaveApplicationStateToIniFile.cpp](src/persistence/SaveApplicationStateToIniFile.cpp) and [persistence/LoadApplicationStateFromIniFile.cpp](src/persistence/LoadApplicationStateFromIniFile.cpp)
