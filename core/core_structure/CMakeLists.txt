add_library(collision_body STATIC
    collision_body/include/collision_body.h
    collision_body/src/collision_body.cpp
)

target_include_directories(collision_body
    PUBLIC collision_body/include/
)

add_library(drawable INTERFACE)

add_library(collision_shapes INTERFACE)

target_include_directories(drawable
    INTERFACE drawable/include/
)

target_include_directories(collision_shapes INTERFACE
    collision_shapes/include
)

target_link_libraries(collision_body PUBLIC
    drawable
    glm
)