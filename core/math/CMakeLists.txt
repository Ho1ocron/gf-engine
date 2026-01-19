add_library(math STATIC
    include/vector2.h include/vector3.h
    src/vector2.cpp src/vector3.cpp
)
target_include_directories(math
    PUBLIC include/
)
