add_library(resource_manager STATIC
    ${GF_INCLUDES_PRIVATE}/core/resource_manager/resource_manager.h
    resource_manager.cpp
)
add_library(gfe::resource_manager ALIAS resource_manager)
target_include_directories(resource_manager
    PUBLIC
        ${GF_INCLUDES_PUBLIC}/
        # ${GF_USERINCLUDES}/
)
target_link_libraries(resource_manager PUBLIC
    gfe::core_constants
    gfe_app_constants # defined by user
    gfe::render
    gfe::font
)
