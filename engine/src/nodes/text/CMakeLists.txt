add_library(text STATIC
    ${GFE_INCLUDES_NODES}/text/text.h
    text.cpp
)
add_library(gfe::text ALIAS text)
target_include_directories(text
    PUBLIC
        ${GFE_INCLUDES_PUBLIC}/
        ${GFE_USERINCLUDES}/
    # PRIVATE
    #     ${GFE_INCLUDES_CORE}/
    #     ${GFE_INCLUDES_NODES}/text
)
target_link_libraries(text PUBLIC
    glm::glm
    glad
    # gfe::font
    freetype::freetype
    gfe_app_constants
    # gfe::resource_manager
)
