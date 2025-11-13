file(GLOB_RECURSE SRC_MAIN_CPP
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

file(GLOB_RECURSE SRC_BUFFERS_H
    "${CMAKE_CURRENT_SOURCE_DIR}/buffers/*.h" 
)

file(GLOB_RECURSE SRC_BUFFERS_CPP
    "${CMAKE_CURRENT_SOURCE_DIR}/buffers/*.cpp"
)

file(GLOB_RECURSE SRC_CAMERA_H
    "${CMAKE_CURRENT_SOURCE_DIR}/camera/*.h"
)

file(GLOB_RECURSE SRC_CAMERA_CPP
    "${CMAKE_CURRENT_SOURCE_DIR}/camera/*.cpp"
)

file(GLOB_RECURSE SRC_CONFIG_H
    "${CMAKE_CURRENT_SOURCE_DIR}/config/*.h"
)

file(GLOB_RECURSE SRC_PERSISTENCE_H
    "${CMAKE_CURRENT_SOURCE_DIR}/persistence/*.h"
)

file(GLOB_RECURSE SRC_PERSISTENCE_CPP
    "${CMAKE_CURRENT_SOURCE_DIR}/persistence/*.cpp"
)

file(GLOB_RECURSE SRC_VOLUMEDATA_H
    "${CMAKE_CURRENT_SOURCE_DIR}/volumedata/*.h"
)

file(GLOB_RECURSE SRC_VOLUMEDATA_CPP
    "${CMAKE_CURRENT_SOURCE_DIR}/volumedata/*.cpp"
)

file(GLOB_RECURSE SRC_CONTEXT_H
    "${CMAKE_CURRENT_SOURCE_DIR}/context/*.h" 
)

file(GLOB_RECURSE SRC_CONTEXT_CPP
    "${CMAKE_CURRENT_SOURCE_DIR}/context/*.cpp"
)

file(GLOB_RECURSE SRC_GUI_H
    "${CMAKE_CURRENT_SOURCE_DIR}/gui/*.h" 
)

file(GLOB_RECURSE SRC_GUI_CPP
    "${CMAKE_CURRENT_SOURCE_DIR}/gui/*.cpp"
)

file(GLOB_RECURSE SRC_IMGUI_H
    "${CMAKE_CURRENT_SOURCE_DIR}/imgui/*.h" 
)

file(GLOB_RECURSE SRC_IMGUI_CPP
    "${CMAKE_CURRENT_SOURCE_DIR}/imgui/*.cpp"
)

file(GLOB_RECURSE SRC_INPUT_H
    "${CMAKE_CURRENT_SOURCE_DIR}/input/*.h" 
)

file(GLOB_RECURSE SRC_INPUT_CPP
    "${CMAKE_CURRENT_SOURCE_DIR}/input/*.cpp"
)

file(GLOB_RECURSE SRC_LIGHTS_H
    "${CMAKE_CURRENT_SOURCE_DIR}/lights/*.h" 
)

file(GLOB_RECURSE SRC_LIGHTS_CPP
    "${CMAKE_CURRENT_SOURCE_DIR}/lights/*.cpp" 
)

file(GLOB_RECURSE SRC_PRIMITIVES_H
    "${CMAKE_CURRENT_SOURCE_DIR}/primitives/*.h"
)

file(GLOB_RECURSE SRC_PRIMITIVES_CPP
    "${CMAKE_CURRENT_SOURCE_DIR}/primitives/*.cpp"
)

file(GLOB_RECURSE SRC_RENDERPASS_H
    "${CMAKE_CURRENT_SOURCE_DIR}/renderpass/*.h"
)

file(GLOB_RECURSE SRC_RENDERPASS_CPP
    "${CMAKE_CURRENT_SOURCE_DIR}/renderpass/*.cpp"
)

file(GLOB_RECURSE SRC_SHADER_H
    "${CMAKE_CURRENT_SOURCE_DIR}/shader/*.h"
)

file(GLOB_RECURSE SRC_SHADER_CPP
    "${CMAKE_CURRENT_SOURCE_DIR}/shader/*.cpp"
)

file(GLOB_RECURSE SRC_SHADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.vert"
    "${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.geom"
    "${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.frag"
)

file(GLOB_RECURSE SRC_STORAGE_H
    "${CMAKE_CURRENT_SOURCE_DIR}/storage/*.h"
)

file(GLOB_RECURSE SRC_STORAGE_CPP
    "${CMAKE_CURRENT_SOURCE_DIR}/storage/*.cpp"
)

file(GLOB_RECURSE SRC_TEXTURES_H
    "${CMAKE_CURRENT_SOURCE_DIR}/textures/*.h"
)

file(GLOB_RECURSE SRC_TEXTURES_CPP
    "${CMAKE_CURRENT_SOURCE_DIR}/textures/*.cpp"
)

file(GLOB_RECURSE SRC_TRANSFERFUNCTION_H
    "${CMAKE_CURRENT_SOURCE_DIR}/transferfunction/*.h"
)

file(GLOB_RECURSE SRC_TRANSFERFUNCTION_CPP
    "${CMAKE_CURRENT_SOURCE_DIR}/transferfunction/*.cpp"
)

file(GLOB_RECURSE SRC_UTILS_H
    "${CMAKE_CURRENT_SOURCE_DIR}/utils/*.h"
)

file(GLOB_RECURSE SRC_UTILS_CPP
    "${CMAKE_CURRENT_SOURCE_DIR}/utils/*.cpp"
)

source_group("buffers\\Header Files" FILES ${SRC_BUFFERS_H})
source_group("buffers\\Source Files" FILES ${SRC_BUFFERS_CPP})

source_group("camera\\Header Files" FILES ${SRC_CAMERA_H})
source_group("camera\\Source Files" FILES ${SRC_CAMERA_CPP})

source_group("config" FILES ${SRC_CONFIG_H})

source_group("persistence\\Header Files" FILES ${SRC_PERSISTENCE_H})
source_group("persistence\\Source Files" FILES ${SRC_PERSISTENCE_CPP})

source_group("volumedata\\Header Files" FILES ${SRC_VOLUMEDATA_H})
source_group("volumedata\\Source Files" FILES ${SRC_VOLUMEDATA_CPP})

source_group("context\\Header Files" FILES ${SRC_CONTEXT_H})
source_group("context\\Source Files" FILES ${SRC_CONTEXT_CPP})

source_group("gui\\Header Files" FILES ${SRC_GUI_H})
source_group("gui\\Source Files" FILES ${SRC_GUI_CPP})

source_group("imgui\\Header Files" FILES ${SRC_IMGUI_H})
source_group("imgui\\Source Files" FILES ${SRC_IMGUI_CPP})

source_group("input\\Header Files" FILES ${SRC_INPUT_H})
source_group("input\\Source Files" FILES ${SRC_INPUT_CPP})

source_group("lights\\Header Files" FILES ${SRC_LIGHTS_H})
source_group("lights\\Source Files" FILES ${SRC_LIGHTS_CPP})

source_group("primitives\\Header Files" FILES ${SRC_PRIMITIVES_H})
source_group("primitives\\Source Files" FILES ${SRC_PRIMITIVES_CPP})

source_group("renderpass\\Header Files" FILES ${SRC_RENDERPASS_H})
source_group("renderpass\\Source Files" FILES ${SRC_RENDERPASS_CPP})

source_group("shader\\Header Files" FILES ${SRC_SHADER_H})
source_group("shader\\Source Files" FILES ${SRC_SHADER_CPP})

source_group("shaders" FILES ${SRC_SHADERS})

source_group("storage\\Header Files" FILES ${SRC_STORAGE_H})
source_group("storage\\Source Files" FILES ${SRC_STORAGE_CPP})

source_group("textures\\Header Files" FILES ${SRC_TEXTURES_H})
source_group("textures\\Source Files" FILES ${SRC_TEXTURES_CPP})

source_group("transferfunction\\Header Files" FILES ${SRC_TRANSFERFUNCTION_H})
source_group("transferfunction\\Source Files" FILES ${SRC_TRANSFERFUNCTION_CPP})

source_group("utils\\Header Files" FILES ${SRC_UTILS_H})
source_group("utils\\Source Files" FILES ${SRC_UTILS_CPP})


add_executable(${PROJECT_NAME}
    ${SRC_BUFFERS_H}
    ${SRC_BUFFERS_CPP}
    ${SRC_CAMERA_H}
    ${SRC_CAMERA_CPP}
    ${SRC_CONFIG_H}
    ${SRC_PERSISTENCE_H}
    ${SRC_PERSISTENCE_CPP}
    ${SRC_VOLUMEDATA_H}
    ${SRC_VOLUMEDATA_CPP}
    ${SRC_CONTEXT_H}
    ${SRC_CONTEXT_CPP}
    ${SRC_GUI_H}
    ${SRC_GUI_CPP}
    ${SRC_IMGUI_H}
    ${SRC_IMGUI_CPP}
    ${SRC_INPUT_H}
    ${SRC_INPUT_CPP}
    ${SRC_MAIN_CPP}
    ${SRC_LIGHTS_H}
    ${SRC_LIGHTS_CPP}
    ${SRC_PRIMITIVES_H}
    ${SRC_PRIMITIVES_CPP}
    ${SRC_RENDERPASS_H}
    ${SRC_RENDERPASS_CPP}
    ${SRC_SHADER_H}
    ${SRC_SHADER_CPP}
    ${SRC_SHADERS}
    ${SRC_STORAGE_H}
    ${SRC_STORAGE_CPP}
    ${SRC_TEXTURES_H}
    ${SRC_TEXTURES_CPP}
    ${SRC_TRANSFERFUNCTION_H}
    ${SRC_TRANSFERFUNCTION_CPP}
    ${SRC_UTILS_H}
    ${SRC_UTILS_CPP}
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    glad::glad
    glfw
    glm::glm
    opengl32
)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

install(TARGETS ${PROJECT_NAME} PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_WRITE GROUP_EXECUTE WORLD_READ WORLD_WRITE WORLD_EXECUTE)
