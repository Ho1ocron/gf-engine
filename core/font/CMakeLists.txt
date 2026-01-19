add_library(font STATIC
    include/font.h
    src/font.cpp
)
target_include_directories(font
    PUBLIC include/
)
target_link_libraries(font PUBLIC
    globals
    render
    freetype
)
