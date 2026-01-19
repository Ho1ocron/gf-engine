cmake_minimum_required(VERSION 3.14)
project(graphics-engine-core)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# see core_constants.h
# add_compile_definitions(
#     SHADER_DIR="core_assets/shaders/"
# )

# third-party libs
add_subdirectory(libs/glfw/)
add_subdirectory(libs/freetype/)
add_subdirectory(libs/glm/)
add_library(glad STATIC
    libs/glad/src/glad.c
)
target_include_directories(glad
    PUBLIC libs/glad/include/
)

# our code
add_library(core_globals INTERFACE constants/core_constants.h)

add_library(engine STATIC
    src/engine.cpp
    include/engine.h
)

target_include_directories(engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(engine PUBLIC
    glad
    glm
    glfw
    camera
    drawable
    freetype
    label
    text
    character_body_2d
    utils
    input
)

# target_link_libraries(input PUBLIC glfw)


target_include_directories(core_globals PUBLIC INTERFACE constants/)
add_subdirectory(math/)
add_subdirectory(render/)
add_subdirectory(font/)
add_subdirectory(resource_manager/)
add_subdirectory(core_structure/)
add_subdirectory(node/)
add_subdirectory(utils/)
add_subdirectory(input/)
add_custom_target(copy_core_assets
COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)

# target_link_libraries(engine PUBLIC
#     drawable
#     glm
#     glad
# )
