add_library(render STATIC
    ${GF_INCLUDES_PRIVATE}/core/render/shader.h
    ${GF_INCLUDES_PRIVATE}/core/render/texture.h
    shader.cpp
    texture.cpp
)
add_library(gfe::render ALIAS render)
target_include_directories(render
    PUBLIC
        ${GF_INCLUDES_PUBLIC}/
)
target_link_libraries(render PUBLIC
    glad
    glm::glm
    gfe::core_constants
)
