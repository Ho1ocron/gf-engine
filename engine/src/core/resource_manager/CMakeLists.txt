add_library(resource_manager STATIC
    ${GFE_INCLUDES_CORE}/resource_manager/resource_manager.h
    resource_manager.cpp
)
add_library(gfe::resource_manager ALIAS resource_manager)
target_include_directories(resource_manager
    PUBLIC
        ${GFE_INCLUDES_PUBLIC}/
        ${GFE_USERINCLUDES}/
    PRIVATE
    #     ${GFE_INCLUDES_CORE}/
    #     ${GFE_INCLUDES_ENGINE}/
        # ${GFE_USERINCLUDES}/
)
target_link_libraries(resource_manager PUBLIC
    gfe::core_constants
    gfe_app_constants # defined by user
    gfe::render
    gfe::font
)
