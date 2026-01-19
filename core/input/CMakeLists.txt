add_library(input STATIC
    include/input.h
    src/input.cpp
)
target_include_directories(input
    PUBLIC include/
)
target_link_libraries(input PUBLIC
    utils
    glfw
)
