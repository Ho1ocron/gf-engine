add_library(label STATIC
    ${GFE_INCLUDES_NODES}/label/label.h
    label.cpp
)
add_library(gfe::label ALIAS label)
target_include_directories(label
    PUBLIC
        ${GFE_INCLUDES_PUBLIC}/
        ${GFE_USERINCLUDES}/
    # PRIVATE
    #     ${GFE_INCLUDES_CORE}/
    #     ${GFE_INCLUDES_NODES}/label
)
target_link_libraries(label PUBLIC
    glm::glm
    gfe::font
    gfe::resource_manager
    gfe_app_constants
)
