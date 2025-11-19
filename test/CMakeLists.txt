# The test application

set(TEST_EXECUTABLE_NAME VolumeRendererTest)

set(TEST_SRC_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")

set(SRC_MAIN_CPP ${TEST_SRC_ROOT}/main.cpp)

file(GLOB_RECURSE TEST_SRC_BUFFERS_CPP
    "${TEST_SRC_ROOT}/buffers/*.cpp"
)

file(GLOB_RECURSE TEST_SRC_CAMERA_CPP
    "${TEST_SRC_ROOT}/camera/*.cpp"
)

file(GLOB_RECURSE TEST_SRC_CONTEXT_CPP
    "${TEST_SRC_ROOT}/context/*.cpp"
)

file(GLOB_RECURSE TEST_SRC_GUI_CPP
    "${TEST_SRC_ROOT}/gui/*.cpp"
)

file(GLOB_RECURSE TEST_SRC_INPUT_CPP
    "${TEST_SRC_ROOT}/input/*.cpp"
)

file(GLOB_RECURSE TEST_SRC_LIGHTS_CPP
    "${TEST_SRC_ROOT}/lights/*.cpp"
)

file(GLOB_RECURSE TEST_SRC_PERSISTENCE_CPP
    "${TEST_SRC_ROOT}/persistence/*.cpp"
)

file(GLOB_RECURSE TEST_SRC_PRIMITIVES_CPP
    "${TEST_SRC_ROOT}/primitives/*.cpp"
)

file(GLOB_RECURSE TEST_SRC_RENDERPASS_CPP
    "${TEST_SRC_ROOT}/renderpass/*.cpp"
)

source_group("buffers" FILES ${TEST_SRC_BUFFERS_CPP})
source_group("camera" FILES ${TEST_SRC_CAMERA_CPP})
source_group("context" FILES ${TEST_SRC_CONTEXT_CPP})
source_group("gui" FILES ${TEST_SRC_GUI_CPP})
source_group("input" FILES ${TEST_SRC_INPUT_CPP})
source_group("lights" FILES ${TEST_SRC_LIGHTS_CPP})
source_group("persistence" FILES ${TEST_SRC_PERSISTENCE_CPP})
source_group("primitives" FILES ${TEST_SRC_PRIMITIVES_CPP})
source_group("renderpass" FILES ${TEST_SRC_RENDERPASS_CPP})

source_group("" FILES ${SRC_MAIN_CPP})

add_executable(${TEST_EXECUTABLE_NAME}
    ${TEST_SRC_BUFFERS_CPP}
    ${TEST_SRC_CAMERA_CPP}
    ${TEST_SRC_CONTEXT_CPP}
    ${TEST_SRC_GUI_CPP}
    ${TEST_SRC_INPUT_CPP}
    ${TEST_SRC_LIGHTS_CPP}
    ${TEST_SRC_PERSISTENCE_CPP}
    ${TEST_SRC_PRIMITIVES_CPP}
    ${TEST_SRC_RENDERPASS_CPP}
    ${SRC_MAIN_CPP}
)

target_include_directories(${TEST_EXECUTABLE_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(${TEST_EXECUTABLE_NAME}
    GTest::gtest
    GTest::gmock
    VolumeRendererLib)

add_test(NAME BuffersTest COMMAND ${TEST_EXECUTABLE_NAME})

install(TARGETS ${TEST_EXECUTABLE_NAME}
    DESTINATION bin/test
    PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_WRITE GROUP_EXECUTE WORLD_READ WORLD_WRITE WORLD_EXECUTE)

# Install required DLLs to bin/test
install(FILES $<TARGET_RUNTIME_DLLS:${TEST_EXECUTABLE_NAME}> DESTINATION bin/test)
