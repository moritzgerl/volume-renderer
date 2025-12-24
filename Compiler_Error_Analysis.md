I have analyzed the build errors resulting from deleting copy constructors in `Texture`, `Shader`, and `FrameBuffer` (to enforce RAII).

**The Cause:**
The errors were caused by initializing `std::vector`s using initializer lists (e.g., `return { obj1, obj2 };`) in the factory functions. `std::initializer_list` elements are `const` and require copy semantics, which conflicted with the deleted copy constructors of the now move-only types.

**The Fix:**
I refactored the following files to use `std::vector::reserve` followed by `push_back` (for moved objects) or `emplace_back` (for in-place construction). This avoids `std::initializer_list` and correctly utilizes move semantics.

1.  **`src/textures/MakeTextures.cpp`**: Refactored `MakeTextures` to construct the vector incrementally using `push_back` (for the result of `MakeVolumeDataTexture`) and `emplace_back` (for other textures).
2.  **`src/shader/MakeShaders.cpp`**: Refactored `MakeShaders` to use `push_back` with `CreateShader`.
3.  **`src/buffers/MakeFrameBuffers.cpp`**: Refactored `MakeFrameBuffers` to use `emplace_back` for creating framebuffers.

These changes ensure the code compiles correctly while maintaining strict RAII ownership of OpenGL resources.
