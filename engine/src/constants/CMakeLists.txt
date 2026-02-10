add_library(engine_constants INTERFACE
    ${GFE_INCLUDES_ENGINE}/constants/texture_units.h
    ${GFE_INCLUDES_ENGINE}/constants/types.h
)
add_library(gfe::engine_constants ALIAS engine_constants)
target_include_directories(engine_constants
    INTERFACE
        ${GFE_INCLUDES_PUBLIC}/
)
