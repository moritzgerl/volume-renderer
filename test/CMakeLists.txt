# The test application

set(TEST_EXECUTABLE_NAME VolumeRendererTest)

set(TEST_SRC_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")

set(SRC_MAIN_CPP ${TEST_SRC_ROOT}/main.cpp)

file(GLOB_RECURSE TEST_SRC_BUFFERS_H
    "${TEST_SRC_ROOT}/buffers/*.h"
)

source_group("buffers" FILES ${TEST_SRC_BUFFERS_H})

source_group("" FILES ${SRC_MAIN_CPP})

add_executable(${TEST_EXECUTABLE_NAME} 
    ${TEST_SRC_BUFFERS_H}
    ${SRC_MAIN_CPP}
)

target_include_directories(${TEST_EXECUTABLE_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(${TEST_EXECUTABLE_NAME}    
    GTest::gtest_main    
    GTest::gmock_main
    VolumeRendererLib)

add_test(NAME BuffersTest COMMAND ${TEST_EXECUTABLE_NAME})

install(TARGETS ${TEST_EXECUTABLE_NAME} PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_WRITE GROUP_EXECUTE WORLD_READ WORLD_WRITE WORLD_EXECUTE) 
