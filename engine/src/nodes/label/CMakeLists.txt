add_library(label STATIC
    ${GF_INCLUDES_PRIVATE}/nodes/label/label.h
    label.cpp
)
add_library(gfe::label ALIAS label)
target_include_directories(label
    PUBLIC
        ${GF_INCLUDES_PUBLIC}/
    # PRIVATE
    #     ${GF_USERINCLUDES}/
)
target_link_libraries(label PUBLIC
    glm::glm
    gfe::font
    gfe::resource_manager
    gfe_app_constants
)
