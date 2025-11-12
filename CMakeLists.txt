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

add_subdirectory(lib)
add_subdirectory(src)
