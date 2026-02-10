add_library(input STATIC
    ${GFE_INCLUDES_CORE}/input/input.h
    input.cpp
)
add_library(gfe::input ALIAS input)
target_include_directories(input
    PUBLIC
        ${GFE_INCLUDES_PUBLIC}/
    # PRIVATE
    #     ${GFE_INCLUDES_CORE}/
    #     # ${GFE_INCLUDES_CORE}/input/
)
target_link_libraries(input PUBLIC
    gfe::core_utils
    glfw::glfw
)
