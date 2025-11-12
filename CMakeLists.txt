cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR} CACHE STRING " " FORCE)

configure_file(cmake/root_directory.h.in cmake/root_directory.h)
include_directories(${CMAKE_BINARY_DIR}/cmake)

if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
endif()

project(volume-renderer)

if(NOT DEFINED CMAKE_PREFIX_PATH)
    set(CMAKE_PREFIX_PATH "C:/Libraries/vcpkg/installed/x64-windows" CACHE PATH "Path to vcpkg installed packages")
endif()

find_package(glad CONFIG REQUIRED)
message(STATUS "Found glad in ${glad_DIR}")

find_package(GLM REQUIRED)
message(STATUS "GLM included at ${GLM_DIR}")

find_package(GLFW3 REQUIRED)
message(STATUS "Found GLFW3 in ${GLFW3_DIR}")

set(LIBS opengl32 glfw3 GLAD CACHE INTERNAL LIBS)

add_subdirectory(src)
