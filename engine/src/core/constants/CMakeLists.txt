add_library(core_constants INTERFACE
    ${GF_INCLUDES_PRIVATE}/core/constants/texture_units.h
    ${GF_INCLUDES_PRIVATE}/core/constants/types.h
)
add_library(gfe::core_constants ALIAS core_constants)
target_include_directories(core_constants
    INTERFACE
        ${GF_INCLUDES_PUBLIC}/
)
