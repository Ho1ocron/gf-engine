add_library(camera STATIC
    ${GFE_INCLUDES_NODES}/camera/camera.h
    camera.cpp
)
add_library(gfe::camera ALIAS camera)
target_include_directories(camera
    PUBLIC
        ${GFE_INCLUDES_PUBLIC}/
    # PRIVATE
    #     ${GFE_INCLUDES_NODES}/camera
)
target_link_libraries(camera PUBLIC
    glm::glm
)
