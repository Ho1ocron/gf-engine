add_library(resource_manager STATIC
    include/resource_manager.h
    src/resource_manager.cpp
)
target_include_directories(resource_manager
    PUBLIC include/
)
target_link_libraries(resource_manager PUBLIC
    globals
    render
    font
)
