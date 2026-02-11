add_library(text STATIC
    ${GF_INCLUDES_PRIVATE}/nodes/text/text.h
    text.cpp
)
add_library(gfe::text ALIAS text)
target_include_directories(text
    PUBLIC
        ${GF_INCLUDES_PUBLIC}/
    PRIVATE
        ${GF_USERINCLUDES}/
)
target_link_libraries(text PUBLIC
    glm::glm
    glad
    # gfe::font
    freetype::freetype
    gfe_app_constants
    # gfe::resource_manager
)
