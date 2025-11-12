# volume-renderer
Volume rendering demo. Basic GPU volume raycasting with a simple GUI and persistence.

<span style="color:red; font-weight:700;">⚠ work in progress</span>

&nbsp;

## Screenshot
<p align="left">
  <img src="https://github.com/user-attachments/assets/bb48413f-3e6d-4e02-afeb-7a288995274b" width="700" alt="Volume Renderer Screenshot">
</p>

&nbsp;

## Building

### Dependencies
* OpenGL
* glad
* GLFW
* glm
* ImGui (included in src/imgui)

#### For Windows with [vcpkg](https://github.com/microsoft/vcpkg)
```
vcpkg install opengl glad glfw3 glm
```
Please use CMake to adjust CMAKE_PREFIX_PATH to the path where you have vcpkg packages installed on your machine. CMAKE_PREFIX_PATH defaults to the path on my machine:
```
C:/Libraries/vcpkg/installed/x64-windows
```

### Building on Windows
Tested with:
* Windows 10 64 bit
* CMake 3.31.4
* Visual Studio 17 2022
* x64
* Use default native compilers

Building the INSTALL target will install the binaries to [build]/bin.

&nbsp;

## Running

### Running on Windows
From [build]/bin, run:
```
volume-renderer.exe
```

&nbsp;

## Dataset
The dataset path is currently hardcoded. Please create a folder called datasets next to volume-renderer.exe and place these two files:\
[knee.raw](https://drive.google.com/file/d/1O3l4bhImrU0P-hzkCiHWina0UrVD3WqM/view?usp=drive_link)\
[knee.ini](https://drive.google.com/file/d/199tYRytMlkCsYgNwjp-3bxSs7khPzBfg/view?usp=drive_link)

The knee dataset is courtesy of:\
http://volume.open-terrain.org\
http://volume.open-terrain.org/Knee.pvm

I converted it to knee.raw with pvm2raw in:\
https://sourceforge.net/projects/volren/

I used Claude Code to generate knee.ini

&nbsp;

## Roadmap
- Refactor transfer function GUI code
- Apply transfer function
- Write documentation
- Write tests
- Lighting
- Screen-space Ambient Occlusion (SSAO)
- Physics-based Rendering

&nbsp;

## Third-Party Libraries

This project uses the following open-source libraries:

OpenGL — API specification by the [Khronos Group](https://www.khronos.org/opengl/)\
[GLAD](https://github.com/Dav1dde/glad) — Licensed under the MIT License\
[GLFW](https://www.glfw.org/) — Licensed under the zlib/libpng License\
[GLM](https://github.com/g-truc/glm) — Licensed under the MIT License\
[Dear ImGui](https://github.com/ocornut/imgui) — Licensed under the MIT License  

