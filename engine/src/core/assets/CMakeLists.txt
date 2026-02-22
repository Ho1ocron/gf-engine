# link this library to include paths
add_library(core_assets INTERFACE
    ${GF_INCLUDES_GENERATED_PRIVATE}/core/assets/paths.h
)
add_library(gfe::core_assets ALIAS core_assets)
target_include_directories(core_assets
    INTERFACE
        ${GF_INCLUDES_GENERATED_PUBLIC}/
)

# .h.in files should not be in include/, so they are locally here
configure_file(paths.h.in ${GF_INCLUDES_GENERATED_PRIVATE}/core/assets/paths.h @ONLY)

# INTERFACE target cannot have POST_BUILD task, so see root CMakeLists.txt
# add_custom_command(TARGET core_assets POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_directory
#         "${CMAKE_CURRENT_SOURCE_DIR}/assets"
#         "${GF_ASSETS_DIR}/core/"
#     COMMENT "gfe::core_assets::Copying assets..."
# )
