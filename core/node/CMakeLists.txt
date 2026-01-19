add_library(label STATIC
    label/include/label.h
    label/src/label.cpp
)
target_include_directories(label
    PUBLIC label/include/
)
target_link_libraries(label PUBLIC
    font
    resource_manager
)

add_library(text STATIC
    text/include/text.h
    text/src/text.cpp
)
target_include_directories(text
    PUBLIC text/include/
)
target_link_libraries(text PUBLIC
    freetype
    font
    resource_manager
    glm
    glad
    drawable
)

add_library(camera STATIC
    camera/include/camera.h
    camera/src/camera.cpp
)

target_link_libraries(camera PUBLIC
    glm
)

target_link_libraries(collision_body PUBLIC 
    glad
)

target_include_directories(camera
    PUBLIC camera/include/
)


# add_library(drawable2d STATIC
#    drawable/include/drawable2d.h 
# )

# target_include_directories(drawable2d PUBLIC 
#     drawable2d/include
# )


add_library(character_body_2d STATIC
    character_body_2d/include/character_body_2d.h
    character_body_2d/src/character_body_2d.cpp
)

target_include_directories(character_body_2d
    PUBLIC character_body_2d/include/
)



target_link_libraries(character_body_2d PUBLIC
    glad
    glm
    collision_body
    collision_shapes
    drawable
) 

target_link_libraries(collision_body PUBLIC 
    drawable
)