add_library(idrawable INTERFACE
    ${GFE_INCLUDES_NODES}/idrawable/idrawable.h
)
add_library(gfe::idrawable ALIAS idrawable)
target_include_directories(idrawable
    INTERFACE
        ${GFE_INCLUDES_PUBLIC}/
)
# target_link_libraries(idrawable PUBLIC
# )
