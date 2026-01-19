cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(graphics-engine)

# see constants.h (core/constants/core_constants.h and test_app/constants.h)
# add_compile_definitions(
#   # SHADER_DIR="assets/shaders/"
#   # FONT_DIR="assets/fonts/"
# )

add_executable(app
    test_app/main.cpp
    # core/src/engine.cpp
    # test_app/app.cpp
)

# include the engine
add_subdirectory(core/)
add_library(globals INTERFACE test_app/constants.h)
target_include_directories(globals PUBLIC INTERFACE test_app/)
# target_include_directories(engine
#     INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/core/include/GF_ENGINE  # directory containing engine.h
# )
target_link_libraries(app PUBLIC
    glfw
    glad
    freetype
    glm
    math
    render
    resource_manager
    font
    label
    camera
    globals
    drawable
    engine
    text
    input
)
add_custom_target(copy_assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)
add_dependencies(app copy_assets)
add_dependencies(app copy_core_assets)
