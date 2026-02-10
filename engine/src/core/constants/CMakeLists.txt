add_library(core_constants INTERFACE
    ${GFE_INCLUDES_CORE}/constants/texture_units.h
    ${GFE_INCLUDES_CORE}/constants/types.h
)
add_library(gfe::core_constants ALIAS core_constants)
target_include_directories(core_constants
    INTERFACE
        ${GFE_INCLUDES_PUBLIC}/
)
# target_link_libraries(core_constants PUBLIC
# )
