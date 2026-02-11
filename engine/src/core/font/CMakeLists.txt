add_library(font STATIC
    ${GF_INCLUDES_PRIVATE}/core/font/font.h
    font.cpp
)
add_library(gfe::font ALIAS font)
target_include_directories(font
    PUBLIC
        ${GF_INCLUDES_PUBLIC}/
)
target_link_libraries(font PUBLIC
    freetype::freetype
    gfe::core_constants
    gfe::render
)
