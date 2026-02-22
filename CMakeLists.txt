cmake_minimum_required(VERSION 3.14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(my_app)

# provide all libraries for GF instead of using FetchContent
set(GF_LIB_PROVIDED_GLFW ON)
set(GF_LIB_PROVIDED_GLM ON)
set(GF_LIB_PROVIDED_FREETYPE ON)
add_subdirectory(libs/glfw/)
add_subdirectory(libs/freetype/)
add_subdirectory(libs/glm/)
set(GF_USERINCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/app/gfe)
set(GF_USER_ASSETS_PATH "assets/")

# constants for gfe to utilize
add_library(gfe_app_constants INTERFACE
    app/gfe/constants/paths.h
)
target_link_libraries(gfe_app_constants
    INTERFACE
        gfe::core_assets
)
target_include_directories(gfe_app_constants
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/app/
)

add_subdirectory(engine)

add_executable(app app/main.cpp)

# target_link_libraries(gfe::gfe PRIVATE
#     glfw3::glfw3
#     glm::glm
#     freetype::freetype
# )
target_link_libraries(app PRIVATE
    gfe::gfe
    gfe::input
    gfe::text
    gfe::camera
    gfe::core_utils
    gfe::core_assets
    gfe::label
)

add_custom_command(TARGET app POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:app>/assets"
    COMMENT "app::Copying assets..."
)
