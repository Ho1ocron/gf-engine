add_library(render STATIC
    include/shader.h
    include/texture.h
    src/shader.cpp
    src/texture.cpp
)
target_include_directories(render
    PUBLIC include/
)
target_link_libraries(render PUBLIC
    glad
    core_globals
    glm
)
