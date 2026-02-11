add_library(engine_constants INTERFACE
    ${GF_INCLUDES_PRIVATE}/constants/texture_units.h
    ${GF_INCLUDES_PRIVATE}/constants/types.h
)
add_library(gfe::engine_constants ALIAS engine_constants)
target_include_directories(engine_constants
    INTERFACE
        ${GF_INCLUDES_PUBLIC}/
)
