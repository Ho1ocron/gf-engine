add_library(render STATIC
    ${GFE_INCLUDES_CORE}/render/shader.h
    ${GFE_INCLUDES_CORE}/render/texture.h
    shader.cpp
    texture.cpp
)
add_library(gfe::render ALIAS render)
target_include_directories(render
    PUBLIC
        ${GFE_INCLUDES_PUBLIC}/
    # PRIVATE
    #     ${GFE_INCLUDES_CORE}/render/
    #     ${GFE_INCLUDES_CORE}/
)
target_link_libraries(render PUBLIC
    glad
    glm::glm
    gfe::core_constants
)
