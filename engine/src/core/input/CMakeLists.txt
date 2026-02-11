add_library(input STATIC
    ${GF_INCLUDES_PRIVATE}/core/input/input.h
    input.cpp
)
add_library(gfe::input ALIAS input)
target_include_directories(input
    PUBLIC
        ${GF_INCLUDES_PUBLIC}/
)
target_link_libraries(input PUBLIC
    gfe::core_utils
    glfw::glfw
)
