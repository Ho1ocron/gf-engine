add_library(font STATIC
    ${GFE_INCLUDES_CORE}/font/font.h
    font.cpp
)
add_library(gfe::font ALIAS font)
target_include_directories(font
    PUBLIC
        ${GFE_INCLUDES_PUBLIC}/
    # PRIVATE
    #     ${GFE_INCLUDES_CORE}/
    #     ${GFE_INCLUDES_CORE}/font/
)
target_link_libraries(font PUBLIC
    freetype::freetype
    gfe::core_constants
    gfe::render
)
