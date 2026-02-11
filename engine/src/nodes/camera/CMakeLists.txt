add_library(camera STATIC
    ${GF_INCLUDES_PRIVATE}/nodes/camera/camera.h
    camera.cpp
)
add_library(gfe::camera ALIAS camera)
target_include_directories(camera
    PUBLIC
        ${GF_INCLUDES_PUBLIC}/
)
target_link_libraries(camera PUBLIC
    glm::glm
)
